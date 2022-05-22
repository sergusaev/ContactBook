#include "clientmanager.h"
#include <QTimer>

ClientManager::ClientManager()
{
    connectSocketSignals();
}

ClientManager &ClientManager::instance()
{
    static ClientManager instance;
    return instance;
}

bool ClientManager::sendPackage(const net::Package &package)
{
    if(m_state == net::ConnectionState::Connected) {
        qDebug()<<"Connection state: connected";
    } else {
        qDebug()<<"Connection state: disconnected";
        return false;
    }
    m_serverSocket.write(package.rawData());
    return true;
}

void ClientManager::onSocketError(QAbstractSocket::SocketError socketError)
{
    qCritical() << "Socket error happened: " << socketError;

    QTimer::singleShot(reconnectionTime(), this, &ClientManager::connectToServer);

    emit reconnectionTimerStarted();
}

void ClientManager::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "Socket state changed: " << socketState;

    switch (socketState)
    {
    case QAbstractSocket::SocketState::BoundState:
    case QAbstractSocket::SocketState::ConnectedState:
    {
        m_state = net::ConnectionState::Connected;
        break;
    }
    case QAbstractSocket::SocketState::ClosingState:
    case QAbstractSocket::SocketState::UnconnectedState:
    {
        m_state = net::ConnectionState::Disconnected;
        break;
    }
    default:
    {
        m_state = net::ConnectionState::Connecting;
    }
    }

    emit connectionStateChanged(m_state);
}

void ClientManager::onDataRecieved()
{
    QMutexLocker locker(&m_mux);
    QDataStream in {&m_serverSocket};
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    forever {
        in.startTransaction();

        net::Package inputPackage;
        in >> inputPackage;

        if (!in.commitTransaction())
        {
            break;
        }

#ifdef DEBUG_OUTPUT
        QString currPackageType;

        switch(inputPackage.type()){
        case net::PackageType::CONTACTS_RESPONSE:
            currPackageType = "CONTACT_RESPONSE";
            break;
        case net::PackageType::ADD_CONTACT_RESPONSE:
            currPackageType = "ADD_CONTACT_RESPONSE";
            break;
        case net::PackageType::REMOVE_CONTACT_RESPONSE:
            currPackageType = "REMOVE_CONTACT_RESPONSE";
            break;
        case net::PackageType::UPDATE_CONTACT_RESPONSE:
            currPackageType = "UPDATE_CONTACT_RESPONSE";
            break;
        default:
            currPackageType = "INVALID";
            break;
        }
        qDebug() << "Recieved package with type " << currPackageType;
#endif

        handlePackage(inputPackage);
    }
}

void ClientManager::connectToServer()
{
    qDebug() << "Connecting to server...";

    if (!m_connectionSettings)
    {
        qCritical() << "Cannot connect! Connection settings are not initialized!";
        return;
    }

    m_serverSocket.connectToHost(m_connectionSettings->hostArgument(),
                                 static_cast<quint16>(m_connectionSettings->portArgument().toUInt()));
}

void ClientManager::connectSocketSignals()
{
    connect(&m_serverSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &ClientManager::onSocketError);
    connect(&m_serverSocket, &QAbstractSocket::stateChanged,
            this, &ClientManager::onSocketStateChanged);
    connect(&m_serverSocket, &QAbstractSocket::readyRead,
            this, &ClientManager::onDataRecieved);
}

void ClientManager::handlePackage(net::Package &package)
{
    switch (package.type())
    {
    case net::PackageType::CONTACTS_RESPONSE:
    {
        handleContactsResponsePackage(package);
        break;
    }
    case net::PackageType::ADD_CONTACT_RESPONSE:
    {
        handleAddContactResponsePackage(package);
        break;
    }
    case net::PackageType::REMOVE_CONTACT_RESPONSE:
    {
        handleRemoveContactResponsePackage(package);
        break;
    }
    case net::PackageType::UPDATE_CONTACT_RESPONSE:
    {
        handleUpdateContactResponsePackage(package);
        break;
    }
    default: {
        qWarning() << "Invalid package!";
    }
    }
}

void ClientManager::handleContactsResponsePackage(const net::Package &package)
{
    std::vector<QVariant> data;
    QVariant packageData {package.data()};

#ifdef DEBUG_OUTPUT
//    qDebug() << "";
//    qDebug() << "In function ClientManager::handleContactsResponsePackage(const net::Package &package) recieved data:";
//    qDebug() << packageData;
#endif

    QSequentialIterable contactsData {packageData.value<QSequentialIterable>()};

    for (auto& entry : contactsData)
    {
        data.push_back(std::move(entry));
    }

#ifdef DEBUG_OUTPUT
//    qDebug() << "";
//    qDebug() << "In function ClientManager::handleContactsResponsePackage(const net::Package &package) emitted data:";
//    qDebug() << data;
#endif

    emit contactsResponse(data);
}

void ClientManager::handleAddContactResponsePackage(const net::Package &package)
{

    emit addContactResponse(package.data());
}

void ClientManager::handleRemoveContactResponsePackage(const net::Package &package)
{
    emit removeContactResponse(package.data());
}

void ClientManager::handleUpdateContactResponsePackage(const net::Package &package)
{
    emit updateContactResponse(package.data());
}

void ClientManager::setConnectionSettings(const net::ConnectionArgumentsParser &connectionSettings)
{
    m_connectionSettings = &connectionSettings;
    connectToServer();
}
