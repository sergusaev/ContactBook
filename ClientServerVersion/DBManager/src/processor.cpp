#include <processor.h>
#include "manipulator.h"
#include "selector.h"
#include "dbmapper.h"
#include <mutex>

namespace db
{
struct Processor::ProcessorPrivate
{
    Selector selector;
    Manipulator manipulator;

#ifdef BUILD_TESTS
    void insertMockData();
    std::once_flag initialized;
#endif

};

#ifdef BUILD_TESTS
void Processor::ProcessorPrivate::insertMockData()
{
    manipulator.insertRow("Contacts", {{"Benedict",  "Cumberbatch", "+79816784352"}});
    manipulator.insertRow("Contacts", {{"Cumberdict",  "Faceberbatch", "+9110985637"}});
    manipulator.insertRow("Contacts", {{"Negorit",  "Vdomepech", "+79161673956"}});
    manipulator.insertRow("Contacts", {{"Boomerdict",  "Cyberscotch", "+79110985637"}});
    manipulator.insertRow("Contacts", {{"Cyberpunk",  "Neverplayed", "+79267854693"}});
    manipulator.insertRow("Contacts", {{"Battletoads",  "Lovesomuch", "+79054816382"}});
    manipulator.insertRow("Contacts", {{"Dirtydick",  "Nevertouch", "+79101985637"}});
    manipulator.insertRow("Contacts", {{"Bekmambet",  "Timurtuch", "+79109838604"}});
    manipulator.insertRow("Contacts", {{"Battlefield",  "Counterstrike", "+79151234675"}});
    manipulator.insertRow("Contacts", {{"Benniehill",  "Petrosyan", "+79216783506"}});
    manipulator.insertRow("Contacts", {{"Baralgin",  "Korvalol", "+79058949353"}});
    manipulator.insertRow("Contacts", {{"Nahooya",  "Vvannoytech", "+79111111111"}});
    manipulator.insertRow("Contacts", {{"Boromir",  "Vsrakemech", "+79117893790"}});
}
#endif


db::Processor::Processor()
    : m_d {new ProcessorPrivate {}}
{
#ifdef BUILD_TESTS
    auto inserter = [this] {
        m_d->insertMockData();
    };
    std::call_once(m_d->initialized, inserter);
#endif
}

Processor::~Processor()
{
}

std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> Processor::requestTableData(DBTypes::DBTables table)
{
    std::vector<QVariantList> result;
    const DBTypes::DBResult resultState {m_d->selector.selectAll(tableMapper.at(table), result)};
    return std::make_pair(resultState, std::move(result));
}

std::pair<DBTypes::DBResult, DBTypes::DBIndex> Processor::insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry &recordData)
{
    return m_d->manipulator.insertRow(tableMapper.at(table), recordData);
}

DBTypes::DBResult Processor::removeDataRecord(DBTypes::DBTables table, const DBTypes::DBIndex index)
{
    return m_d->manipulator.removeRow(tableMapper.at(table), index);
}

DBTypes::DBResult Processor::updateDataRecord(DBTypes::DBTables table, const DBTypes::DBIndex index, const DBTypes::DBEntry &updatedRecordData)
{
    return m_d->manipulator.updateRow(tableMapper.at(table), index, updatedRecordData);
}

}
