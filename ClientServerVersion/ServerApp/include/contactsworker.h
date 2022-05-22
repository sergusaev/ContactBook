#ifndef CONTACTSWORKER_H
#define CONTACTSWORKER_H

#include <QObject>
#include "contacts_handler.h"
#include <package.h>

class QTcpSocket;

class ContactsWorker:public QObject {
    Q_OBJECT

public:
    void handleContactsRequest(QTcpSocket* socket);
    void handleAddContactRequest(const net::Package& packageData, QTcpSocket* socket);
    void handleRemoveContactRequest(const net::Package& packageData, QTcpSocket* socket);
    void handleUpdateContactRequest(const net::Package& packageData, QTcpSocket* socket);

signals:
    void contactsRequestCompleted(const net::Package& packageData, QTcpSocket* socket);
    void contactAdditionRequestCompleted(const net::Package& packageData, QTcpSocket* socket);
    void contactRemovalRequestCompleted(const net::Package& packageData, QTcpSocket* socket);
    void contactUpdateRequestCompleted(const net::Package& packageData, QTcpSocket* socket);

private:
    ContactsHandler m_contactsHandler;
};

#endif // CONTACTSWORKER_H
