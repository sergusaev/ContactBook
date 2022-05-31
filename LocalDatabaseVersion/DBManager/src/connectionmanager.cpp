#include "connectionmanager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDir>

using namespace DBTypes;
namespace db
{
namespace
{
    class DBCloser {
    public:
        void operator() (QSqlDatabase* db) {
            db->close();
            QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        }
    };
}

class ConnectionManager::DBManagerPrivate {
public:
    std::unique_ptr<QSqlDatabase, DBCloser> m_database;
    std::string m_dbPath;
    DBState m_state {DBState::OK};
    bool m_isValid {true};

    bool setUp();
    bool setUpWorkspace();
    bool setUpTables();

    void setIsValid(bool isValid);
};

ConnectionManager& ConnectionManager::instance()
{
    static ConnectionManager instance {};
    return instance;
}

std::string ConnectionManager::databasePath() const
{
    return m_d->m_dbPath;
}

DBState ConnectionManager::state() const
{
    return m_d->m_state;
}

bool ConnectionManager::DBManagerPrivate::setUp()
{
    const QString driver {"QSQLITE"};

    if (!QSqlDatabase::isDriverAvailable(driver))
    {
        m_state = DBState::ERROR_NO_DRIVER;
        qWarning() << "Driver " << driver << " is not available.";
        return false;
    }

    if (!setUpWorkspace())
    {
        m_state = DBState::ERROR_WORKSPACE;
        qCritical() << "Workspace setup failed!";
        return false;
    }

    auto* db = new QSqlDatabase {QSqlDatabase::addDatabase(driver)};
    m_database.reset(db);
    m_database->setDatabaseName(QString::fromStdString(m_dbPath));

    qDebug() << "Database name: " << m_database->databaseName();

    if (!m_database->open())
    {
        m_state = DBState::ERROR_OPENING;
        qCritical() << "Error in opening DB " << m_database->databaseName()
                   << " reason: " <<  m_database->lastError().text();
        return false;
    }

    return setUpTables();
}

bool ConnectionManager::DBManagerPrivate::setUpWorkspace()
{
#ifdef BUILD_TESTS
    const QString databaseName {"TestDB"};
#else
    const QString databaseName {"ContactsDB"};
#endif
    const QString location {QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)};
    const QString fullPath {location + "/" + databaseName};

    m_dbPath = fullPath.toStdString();

    QDir dbDirectory {location};
    if (!dbDirectory.exists())
    {
        const bool creationResult {dbDirectory.mkpath(location)};
        qWarning() << "DB directory not exist, creating result: "
                   << creationResult;
    }

    qDebug() << "Data path: " << fullPath;

    return dbDirectory.exists();
}

bool ConnectionManager::DBManagerPrivate::setUpTables()
{
    bool result {true};

    std::vector<QSqlQuery> creationQueries = {
        QSqlQuery {
            "CREATE TABLE IF NOT EXISTS Contacts"
            "("
            "Name TEXT,"
            "Surname TEXT,"
            "PhoneNumber TEXT,"
            "UNIQUE(PhoneNumber)"
            ")"
        }
    };

    for (auto& query : creationQueries)
    {
        if (!query.exec())
        {
            result = false;
            m_state = DBState::ERROR_TABLES;
            qWarning() << "Table creation failed. Reason: "
                       << query.lastError();
        }
        else
        {
            qWarning() << "Table successfully opened or created. Query: " << query.lastQuery();
        }
    }

    return result;
}

void ConnectionManager::DBManagerPrivate::setIsValid(bool isValid)
{
    m_isValid = isValid;
}

bool ConnectionManager::isValid() const
{
    return m_d->m_isValid && m_d->m_database->isValid();
}

ConnectionManager::ConnectionManager()
    : m_d {new DBManagerPrivate {}}
{
    const bool setupResult {m_d->setUp()};
    m_d->setIsValid(setupResult);
}

ConnectionManager::~ConnectionManager()
{
}
}
