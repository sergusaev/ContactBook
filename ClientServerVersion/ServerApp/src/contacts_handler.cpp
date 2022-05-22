#include "contacts_handler.h"
#include <processor.h>
#include <QDebug>

ContactsHandler::ContactsHandler()
    : m_processor {new db::Processor{}}
{

}

ContactsHandler::~ContactsHandler()
{

}

std::vector<QVariant> transform (const std::vector<DBTypes::DBEntry>& source) {
    std::vector<QVariant> target;
    std::transform(source.begin(),
                   source.end(),
                   std::back_inserter(target),
                   [](const DBTypes::DBEntry& entry){return QVariant::fromValue(entry);});

#ifdef DEBUG_OUTPUT
//    qDebug() << "In function transform(const std::vector<DBTypes::DBEntry>& source) transformed data:";
//    for (const auto& t : target) {
//       QVariantList dataList = t.toList();
//       for(const auto& item : dataList) {
//            qDebug() << item;
//        }
//    }
#endif

    return target;
}


std::pair<bool, std::vector<QVariant>> ContactsHandler::requestContactsBrowse()
{

    DBTypes::DBResult result;
    std::vector<DBTypes::DBEntry> entries;
    std::tie(result, entries) = m_processor->requestTableData(DBTypes::DBTables::Contacts);

#ifdef DEBUG_OUTPUT
//    qDebug() << "In function requestContactBrowse() recieved data:";
//    for (const auto& entry : entries) {
//        for(const auto& item : entry) {
//            qDebug() << item;
//        }
//    }
//    if (result == DBTypes::DBResult::OK) {
//        qDebug() << "Result of requestTableData(DBTypes::DBTables::Contacts): OK" << "\n";
//    } else {
//        qDebug() << "Result of requestTableData(DBTypes::DBTables::Contacts): FAIL" << "\n";
//    }
#endif

    return {result == DBTypes::DBResult::OK, transform(entries)};
}

DBTypes::DBIndex ContactsHandler::requestContactAddition(const DBTypes::DBEntry &entry)
{
    DBTypes::DBResult result;
    DBTypes::DBIndex index;
    std::tie(result, index) = m_processor->insertDataRecord(DBTypes::DBTables::Contacts, entry);

#ifdef DEBUG_OUTPUT
//    qDebug() << "";
//    qDebug() << "In function ContactsHandler::requestContactAddition(const DBTypes::DBEntry &entry) data to insert:";
//    qDebug() << entry;
//    qDebug() << "In function ContactsHandler::requestContactAddition(const DBTypes::DBEntry &entry) DB index of inserted data record:" << index;
#endif

    return (result == DBTypes::DBResult::OK) ? index : -1;
}

bool ContactsHandler::requestContactRemoval(const DBTypes::DBIndex index)
{

    DBTypes::DBResult result;
    result = m_processor->removeDataRecord(DBTypes::DBTables::Contacts, index);

#ifdef DEBUG_OUTPUT
//    qDebug() << "";
//    qDebug() << "In function ContactsHandler::requestContactRemoval(const DBTypes::DBIndex index)DB index to remove:" << index;
//    qDebug() << "In function ContactsHandler::requestContactRemoval(const DBTypes::DBIndex index) result of removal:" << (result == DBTypes::DBResult::OK);
#endif

    return result == DBTypes::DBResult::OK;
}

bool ContactsHandler::requestContactUpdate(const DBTypes::DBIndex index, const DBTypes::DBEntry& entry)
{
    DBTypes::DBResult result;
    result = m_processor->updateDataRecord(DBTypes::DBTables::Contacts, index, entry);

#ifdef DEBUG_OUTPUT
    qDebug() << "";
    qDebug() << "In function ContactsHandler::requestContactUpdate(<args>) ID of contact to update:" << index;
    qDebug() << "In function ContactsHandler::requestContactUpdate(<args>) contact data to update:";
    qDebug() << entry;
    qDebug() << "In function ContactsHandler::updateContact(<args>) contact update state:" << (result == DBTypes::DBResult::OK);
#endif

    return result == DBTypes::DBResult::OK;
}

