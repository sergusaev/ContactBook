#include "contactsworker_app.h"


ContactsWorker::ContactsWorker()
    : m_clientManager {ClientManager::instance()}
{
    connect(&m_clientManager, &ClientManager::connectionStateChanged,
            this, &ContactsWorker::onConnectionStateChanged);
    connect(&m_clientManager, &ClientManager::contactsResponse,
            this, &ContactsWorker::onContactsDownloadSucceed);
    connect(&m_clientManager, &ClientManager::addContactResponse,
            this, &ContactsWorker::onContactAdditionSucceed);
    connect(&m_clientManager, &ClientManager::removeContactResponse,
            this, &ContactsWorker::onContactRemovalSucceed);
    connect(&m_clientManager, &ClientManager::updateContactResponse,
            this, &ContactsWorker::onContactUpdateSucceed);
}

bool ContactsWorker::requestBrowseContacts()
{
    const net::Package package {QVariant::fromValue(true), net::PackageType::CONTACTS_REQUEST};
    return m_clientManager.sendPackage(package);
}

bool ContactsWorker::requestContactAddition(const Contact &contact)
{
    QVariantList dataList {QVariant::fromValue(contact.firstName()),
                           QVariant::fromValue(contact.secondName()),
                           QVariant::fromValue(contact.phone())};
    const net::Package package {QVariant::fromValue(dataList), net::PackageType::ADD_CONTACT_REQUEST};
    return m_clientManager.sendPackage(package);
}

bool ContactsWorker::requestContactRemoval(const int modelIndex)
{
    const net::Package package {QVariant::fromValue(modelIndex), net::PackageType::REMOVE_CONTACT_REQUEST};
    return m_clientManager.sendPackage(package);
}

bool ContactsWorker::requestContactUpdate(const DBTypes::DBIndex index, const Contact &updatedContact)
{
    const net::Package package {QVariant::fromValue(QVariantList {QVariant::fromValue(index),
                                                                  QVariant::fromValue(updatedContact.firstName()),
                                                                  QVariant::fromValue(updatedContact.secondName()),
                                                                  QVariant::fromValue(updatedContact.phone())}),
                                net::PackageType::UPDATE_CONTACT_REQUEST};
    return m_clientManager.sendPackage(package);
}

void ContactsWorker::onConnectionStateChanged(net::ConnectionState state)
{
    if (state == net::ConnectionState::Connected)
    {
        requestBrowseContacts();
    }
}


Contact transformQVariantListToContact(QVariantList& dataList) {
    Contact contact;
    contact.setDbID(dataList.first().toInt());
    dataList.pop_front();
    contact.setFirstName(std::move(dataList.first().toString()));
    dataList.pop_front();
    contact.setSecondName(std::move(dataList.first().toString()));
    dataList.pop_front();
    contact.setPhone(std::move(dataList.first().toString()));
    return contact;
}

static std::vector<Contact> transform(const std::vector<QVariant>& source)
{


    std::vector<Contact> target;
    std::transform(source.begin(),
                   source.end(),
                   std::back_inserter(target),
                   [](const QVariant& entry) {
#ifdef DEBUG_OUTPUT
//                                                qDebug() << "";
//                                                qDebug() << "In function transform(const std::vector<QVariant>& source) in contactsworker_app.cpp data before transformation:";
//                                                qDebug() << entry;
#endif
                                                QVariantList dataList = entry.toList();
                                                Contact contact  = transformQVariantListToContact(dataList);
#ifdef DEBUG_OUTPUT
//                                                qDebug() << "";
//                                                qDebug() << "In function transform(const std::vector<QVariant>& source) in contactsworker_app.cpp data after transformation:";
//                                                qDebug() << "Name:" << contact.firstName();
//                                                qDebug() << "Surname:" << contact.secondName();
//                                                qDebug() << "PhoneNumber:" << contact.phone();
//                                                qDebug() << "ID:" << contact.dbID();
#endif
                                                return contact;
                                             });
//        std::transform(source.begin(),
//                       source.end(),
//                       std::back_inserter(target),
//                       [](const QVariant& entry) {
//                                                    qDebug() << "";
//                                                    qDebug() << "In function transform(const std::vector<QVariant>& source) in contactsworker_app.cpp data before transformation:";
//                                                    qDebug() << entry;
//                                                    Contact contact = entry.value<Contact>();
//                                                    qDebug() << "";
//                                                    qDebug() << "In function transform(const std::vector<QVariant>& source) in contactsworker_app.cpp data after transformation:";
//                                                    qDebug() << "Name:" << contact.firstName();
//                                                    qDebug() << "Surname:" << contact.secondName();
//                                                    qDebug() << "PhoneNumber:" << contact.phone();
//                                                    qDebug() << "ID:" << contact.dbID();
//                                                    return contact;
//                                                 });
    return target;
}

void ContactsWorker::onContactsDownloadSucceed(const std::vector<QVariant> &data)
{
    emit browsingContactsCompleted(transform(data));
}

void ContactsWorker::onContactAdditionSucceed(const QVariant& data)
{
    QVariantList dataList = data.toList();
    emit contactAdditionCompleted(std::move(transformQVariantListToContact(dataList)));
}

void ContactsWorker::onContactRemovalSucceed(const QVariant& data)
{
    emit contactRemovalCompleted(data.toInt());
}

void ContactsWorker::onContactUpdateSucceed(const QVariant& data)
{
    QVariantList dataList = data.toList();
    emit contactUpdateCompleted(std::move(transformQVariantListToContact(dataList)));
}


