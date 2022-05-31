#ifndef PROCESSOR_H
#define PROCESSOR_H


#include "dbtypes.h"
#include <memory>

namespace db
{
class Processor
{
public:
    Processor();
    ~Processor();
    std::pair<DBTypes::DBResult,
              std::vector<DBTypes::DBEntry>> requestTableData(DBTypes::DBTables table);

    std::pair<DBTypes::DBResult, DBTypes::DBIndex> insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry& recordData);
    DBTypes::DBResult removeDataRecord(DBTypes::DBTables table, const DBTypes::DBIndex index);
//    DBTypes::DBResult updateDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry& oldRecordData, const DBTypes::DBEntry& updatedRecordData);
    DBTypes::DBResult updateDataRecord(DBTypes::DBTables table, const DBTypes::DBIndex index, const DBTypes::DBEntry& updatedRecordData);

private:
    struct ProcessorPrivate;
    std::unique_ptr<ProcessorPrivate> m_d;
};
}

#endif // PROCESSOR_H
