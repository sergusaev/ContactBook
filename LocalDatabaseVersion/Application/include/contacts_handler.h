#ifndef CONTACTSREADER_H
#define CONTACTSREADER_H

#include <vector>
#include <memory>
#include "contact.h"

namespace db {
class Processor;
}

class ContactsHandler
{
public:
    ContactsHandler();
    ~ContactsHandler();
    std::pair<bool, std::vector<Contact>> requestContactsBrowse();
    DBTypes::DBIndex addContact (const Contact& contact);
    bool removeContact (const DBTypes::DBIndex index);
//    bool updateContact (const Contact& oldContact, const Contact& updatedContact);
    bool updateContact (const DBTypes::DBIndex index, const Contact& updatedContact);

private:
    std::unique_ptr<db::Processor> m_processor;
};

#endif // CONTACTSREADER_H
