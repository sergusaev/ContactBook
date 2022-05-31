#include "contacts_handler.h"
#include "processor.h"
#include <QDebug>

ContactsHandler::ContactsHandler()
    : m_processor {new db::Processor{}}
{

}

ContactsHandler::~ContactsHandler() {

}

std::vector<Contact> transform (const std::vector<DBTypes::DBEntry>& source) {
    std::vector<Contact> target;
    std::transform(source.begin(), source.end(), std::back_inserter(target), [](const DBTypes::DBEntry& entry){
        return Contact { entry[1].toString(),
                    entry[2].toString(),
                    entry[3].toString(),
                    entry[0].toInt()


        };
    });
    return target;
}


std::pair<bool, std::vector<Contact> > ContactsHandler::requestContactsBrowse()
{
    DBTypes::DBResult result;
    std::vector<DBTypes::DBEntry> entries;
    std::tie(result, entries) = m_processor->requestTableData(DBTypes::DBTables::Contacts);
    return {result == DBTypes::DBResult::OK, transform(entries)};
}

DBTypes::DBIndex ContactsHandler::addContact(const Contact &contact)
{
    DBTypes::DBResult result;
    DBTypes::DBIndex index;
    std::tie(result, index) = m_processor->insertDataRecord(DBTypes::DBTables::Contacts,
                                                            {contact.firstName(), contact.secondName(), contact.phone()});
    return (result == DBTypes::DBResult::OK) ? index : -1;
}

bool ContactsHandler::removeContact(const DBTypes::DBIndex index)
{
    DBTypes::DBResult result;
    result = m_processor->removeDataRecord(DBTypes::DBTables::Contacts, index);
    return result == DBTypes::DBResult::OK;
}

bool ContactsHandler::updateContact(const DBTypes::DBIndex index, const Contact &updatedContact)
{
    DBTypes::DBResult result;
    result = m_processor->updateDataRecord(DBTypes::DBTables::Contacts,
                                           index,
                                           {updatedContact.firstName(),
                                            updatedContact.secondName(),
                                            updatedContact.phone()});
    qDebug() << "In function ContactsHandler::updateContact(<args>) ID of contact to update:" << index << "\n";
    return result == DBTypes::DBResult::OK;
}

//bool ContactsHandler::updateContact(const Contact &oldContact, const Contact &updatedContact)
//{
//    DBTypes::DBResult result;
//    result = m_processor->updateDataRecord(DBTypes::DBTables::Contacts,
//                                           {oldContact.firstName(), oldContact.secondName(), oldContact.phone()},
//                                           {updatedContact.firstName(), updatedContact.secondName(), updatedContact.phone()});
//    return result == DBTypes::DBResult::OK;
//}
