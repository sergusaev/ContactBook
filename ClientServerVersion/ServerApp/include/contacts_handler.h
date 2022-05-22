#ifndef CONTACTSREADER_H
#define CONTACTSREADER_H

#include <dbtypes.h>

#include <vector>
#include <memory>
#include <QVariant>


namespace db {
class Processor;
}

class ContactsHandler
{
public:
    ContactsHandler();
    ~ContactsHandler();
    std::pair<bool, std::vector<QVariant> > requestContactsBrowse();
    DBTypes::DBIndex requestContactAddition (const DBTypes::DBEntry& entry);
    bool requestContactRemoval (const DBTypes::DBIndex index);
    bool requestContactUpdate (const DBTypes::DBIndex index, const DBTypes::DBEntry& entry);

private:
    std::unique_ptr<db::Processor> m_processor;
};

#endif // CONTACTSREADER_H
