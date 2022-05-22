#ifndef NETWORKTYPES_H
#define NETWORKTYPES_H

#include <QtGlobal>

namespace net
{
enum class PackageType : qint32 {
    INVALID = 10,
    CONTACTS_REQUEST,
    CONTACTS_RESPONSE,
    ADD_CONTACT_REQUEST,
    ADD_CONTACT_RESPONSE,
    REMOVE_CONTACT_REQUEST,
    REMOVE_CONTACT_RESPONSE,
    UPDATE_CONTACT_REQUEST,
    UPDATE_CONTACT_RESPONSE
};

enum class ConnectionState {
    Connected,
    Disconnected,
    Connecting
};
}

#endif // NETWORKTYPES_H
