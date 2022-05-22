#ifndef CONTACTSWORKER_APP_H
#define CONTACTSWORKER_APP_H

#include <QObject>
#include "contact.h"
#include <networktypes.h>
#include "clientmanager.h"

class ContactsWorker : public QObject
{
    Q_OBJECT
public:
    ContactsWorker();
    bool requestBrowseContacts();
    bool requestContactAddition (const Contact& contact);
    bool requestContactRemoval (const int modelIndex);
    bool requestContactUpdate (const DBTypes::DBIndex index, const Contact& updatedContact);


signals:
    void browsingContactsCompleted(const std::vector<Contact>& data);
    void contactAdditionCompleted(const Contact& contactData);
    void contactRemovalCompleted(const DBTypes::DBIndex index);
    void contactUpdateCompleted(const Contact& contactData);



private slots:
    void onConnectionStateChanged(net::ConnectionState state);
    void onContactsDownloadSucceed(const std::vector<QVariant>& data);
    void onContactAdditionSucceed(const QVariant& data);
    void onContactRemovalSucceed(const QVariant& data);
    void onContactUpdateSucceed(const QVariant& data);

private:
    ClientManager& m_clientManager;
};

#endif // CONTACTSWORKER_APP_H
