#include "manipulator.h"
#include <sstream>
#include "dbmapper.h"

using namespace DBTypes;

namespace db
{

std::pair<DBResult, DBIndex> Manipulator::insertRow(const std::string& tableName, const DBTypes::DBEntry& recordData)
{
    const std::string& query {generateInsertQuery(tableName, recordData.size())};
    const std::pair<DBResult, QSqlQuery>& result {m_executor.execute(query, recordData)};

#ifdef DEBUG_OUTPUT
//    qDebug() << "";
//    qDebug() << "In function Manipulator::insertRow(const std::string& tableName, const DBTypes::DBEntry& recordData) data to insert:";
//    qDebug() << recordData;
#endif

    return std::make_pair(result.first, result.second.lastInsertId().toInt());
}

DBResult Manipulator::removeRow(const std::string& tableName, const DBTypes::DBIndex index)
{

#ifdef DEBUG_OUTPUT
//    qDebug() << "";
//    qDebug() << "In function Manipulator::removeRow(const std::string& tableName, const DBTypes::DBIndex index) QModelIndex to remove:" << index;
#endif

    const std::string& query {generateRemoveQuery(tableName)};

    const std::pair<DBResult, QSqlQuery>& result {m_executor.execute(query, {index})};
    return result.first;
}

DBResult Manipulator::updateRow(const std::string &tableName, const DBTypes::DBIndex indexToUpdate, const DBTypes::DBEntry &updatedRecordData)
{
    const std::string& query {generateUpdateQuery(tableName,updatedRecordData.size())};
    const std::pair<DBResult, QSqlQuery>& result {m_executor.execute(query,
                                                 {updatedRecordData[0],
                                                  updatedRecordData[1],
                                                  updatedRecordData[2],
                                                  indexToUpdate})};
#ifdef DEBUG_OUTPUT
    qDebug() << "In function Manipulator::updateRow(<args>) new contact data: " << updatedRecordData[0]
                                                                                << updatedRecordData[1]
                                                                                << updatedRecordData[2];
    qDebug() << "In function Manipulator::updateRow(<args>) ID of contact to update : " << indexToUpdate << "\n";
#endif
    return result.first;
}


std::string Manipulator::generateBindString(size_t paramCount) const
{
    std::ostringstream bindings;
    std::fill_n(std::ostream_iterator<std::string>(bindings),
                paramCount,
                "?,");
    std::string bindString = bindings.str();
    bindString.pop_back(); // the last ","
    return bindString;
}

std::string Manipulator::generateInsertQuery(const std::string& tableName, size_t paramCount) const
{
    std::string tableColumns = tablesMapping.at(tableName)[0] + ",";
    for(size_t i = 1; i < paramCount; ++i) {
        tableColumns += " " + tablesMapping.at(tableName)[i] + ",";
    }
    tableColumns.pop_back(); //the last ","
    std::string query = "INSERT INTO " + tableName +  " (" + tableColumns + ")" +
                        " VALUES (";

    query += generateBindString(paramCount);
    query += ")";
    return query;
}

std::string Manipulator::generateRemoveQuery(const std::string &tableName) const
{
    std::string query = "DELETE FROM " + tableName +  " WHERE rowid = ?";
    return query;
}

std::string Manipulator::generateUpdateQuery(const std::string &tableName, size_t paramCount) const
{
    std::string query = "UPDATE " + tableName +  " SET ";
    for(size_t i = 0; i < paramCount; ++i) {
        query += tablesMapping.at(tableName)[i] + " = ?,";
    }
    query.pop_back(); // the last ","
    query += " WHERE rowid = ?";
    return query;
}




}
