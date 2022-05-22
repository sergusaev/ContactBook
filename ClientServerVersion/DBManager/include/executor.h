#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <QMap>
#include <QDebug>
#include <QSqlQuery>
#include "connectionmanager.h"

namespace db
{
class Executor
{
public:
    Executor();
    Q_DISABLE_COPY(Executor)

    std::pair<DBTypes::DBResult, QSqlQuery> execute(const std::string& queryText, const QVariantList& args = {});

private:
    ConnectionManager& m_connectionManager;
};
}

#endif // EXECUTOR_H
