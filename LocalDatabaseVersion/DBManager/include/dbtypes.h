#ifndef DBTYPES_H
#define DBTYPES_H
#include <QVariantList>

namespace DBTypes
{
enum class DBResult {
    OK,
    FAIL
};

enum class DBTables {
    Contacts = 1
};

enum class DBState {
    OK,
    ERROR_NO_DRIVER,
    ERROR_WORKSPACE,
    ERROR_TABLES,
    ERROR_OPENING
};

using DBEntry = QVariantList;
using DBIndex = int;
}
#endif // DBTYPES_H
