#ifndef DBMAPPER_H
#define DBMAPPER_H

#include "dbtypes.h"

namespace db
{
static const std::map<DBTypes::DBTables, std::string> tableMapper {
    {DBTypes::DBTables::Contacts, "Contacts"}
};

static const std::map<std::string, std::vector<std::string>> tablesMapping = {
    {"Contacts", {"Name", "Surname", "PhoneNumber"}}
};
}


#endif // DBMAPPER_H
