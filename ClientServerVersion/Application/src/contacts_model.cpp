#include "contacts_model.h"
#include <QQmlEngine>
#include <QDebug>


ContactsModel::ContactsModel()
{
    connect(&m_contactsWorker, &ContactsWorker::browsingContactsCompleted,
                this, &ContactsModel::onContactListDownloaded);
    connect(&m_contactsWorker, &ContactsWorker::contactAdditionCompleted,
            this, &ContactsModel::onContactAdded);
    connect(&m_contactsWorker, &ContactsWorker::contactRemovalCompleted,
            this, &ContactsModel::onContactRemoved);
    connect(&m_contactsWorker, &ContactsWorker::contactUpdateCompleted,
            this, &ContactsModel::onContactUpdated);
//    updateContacts();
    const bool updateResult {updateContacts()};

    if (!updateResult) {
        qWarning() << "Update contacts failed!";
    }
}

void ContactsModel::registerModel(const std::string &modelName)
{
    qmlRegisterType<ContactsModel>(modelName.c_str(), 1, 0, "ContactsModel");
}

QHash<int, QByteArray> ContactsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ContactRoles::NameRole] = "name";
    roles[ContactRoles::SurnameRole] = "surname";
    roles[ContactRoles::PhoneNumberRole] = "phoneNumber";
    return roles;
}

int ContactsModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_contacts.size());
}

QVariant ContactsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount(index)) {
        return {};
    }
    const Contact& contact {m_contacts.at(index.row())};
    switch (role) {
    case ContactRoles::NameRole: {
        return QVariant::fromValue(contact.firstName());
    }
    case ContactRoles::SurnameRole: {
        return QVariant::fromValue(contact.secondName());
    }
    case ContactRoles::PhoneNumberRole: {
        return QVariant::fromValue(contact.phone());
    }
    case ContactRoles::AllElementsRole: {
        return QVariant::fromValue(contact.phone());
    }
    default:
    {
        return true;
    }
    }
}


void ContactsModel::changeContactData(int modelIndex, const Contact &contact)
{
    m_contacts[modelIndex].setFirstName(contact.firstName());
    m_contacts[modelIndex].setSecondName(contact.secondName());
    m_contacts[modelIndex].setPhone(contact.phone());
    emit dataChanged(createIndex(modelIndex, 0), createIndex(modelIndex, 0));

#ifdef DEBUG_OUTPUT
    qDebug() << "In function ContactsModel::changeContactData(<args>) new data: " << contact.firstName() << contact.secondName() << contact.phone();
    qDebug() << "In function ContactsModel::changeContactData(<args>) model index of contact to update: " << modelIndex;
    qDebug() << "In function ContactsModel::changeContactData(<args>) DB index of contact to update: " << m_contacts[modelIndex].dbID();
#endif

}

void ContactsModel::addContact(const Contact& contact)
{

    beginInsertRows(QModelIndex(),rowCount(), rowCount());
    m_contacts.push_back(contact);
    endInsertRows();

#ifdef DEBUG_OUTPUT
    qDebug() << "";
    qDebug() << "New contact database index: " << contact.dbID();
    qDebug() << "New contact model index:" << m_contacts.size() - 1;
//    qDebug() << "Current contacts:";
//    for(const auto& contact : m_contacts) {
//        qDebug() <<  "ID: " << contact.dbID() << " "
//                 <<  "Name: " << contact.firstName() << " "
//                 <<  "Surname: " << contact.secondName() << " "
//                 <<  "PhoneNumber: " << contact.phone() << "\n";
//    }
#endif


}

void ContactsModel::deleteContact(int modelIndex)
{
    beginRemoveRows(QModelIndex(),modelIndex, modelIndex);
    m_contacts.erase(m_contacts.begin() + modelIndex);
    endRemoveRows();

#ifdef DEBUG_OUTPUT
//    qDebug() << "Current contacts:";
//    for(auto& contact : m_contacts) {
//        qDebug() <<  "ID: " << contact.dbID() << " "
//                 <<  "Name: " << contact.firstName() << " "
//                 <<  "Surname: " << contact.secondName() << " "
//                 <<  "PhoneNumber: " << contact.phone();
//    }
#endif

}

void ContactsModel::addContactFromQml(const QString &name, const QString &surname, const QString &phoneNumber)
{
    m_contactsWorker.requestContactAddition({name, surname, phoneNumber});
}

void ContactsModel::deleteContactFromQml(int index)
{
    m_contactsWorker.requestContactRemoval(m_contacts[index].dbID()); //transforming model index into DB rowid
}

void ContactsModel::changeContactDataFromQml(const QString &name, const QString &surname, const QString &phoneNumber, int index)
{
    m_contactsWorker.requestContactUpdate(m_contacts[index].dbID(), {name, surname, phoneNumber});
}


void ContactsModel::onContactListDownloaded(const std::vector<Contact> &data)
{
    beginResetModel();
    m_contacts = data;
    endResetModel();

    qDebug() << "Contact list downloaded!" << rowCount() << " contacts available!";
}

void ContactsModel::onContactAdded(const Contact &data)
{
    addContact(data);
}

void ContactsModel::onContactRemoved(const DBTypes::DBIndex index)
{
    int modelIndex = std::abs(std::distance(m_contacts.begin(), std::find_if(m_contacts.begin(),
                                                                             m_contacts.end(),
                                                                             [&](const Contact& contact){return contact.dbID() == index;})));
    deleteContact(modelIndex);
}

void ContactsModel::onContactUpdated(const Contact& data)
{
    int modelIndex = std::abs(std::distance(m_contacts.begin(), std::find_if(m_contacts.begin(),
                                                                             m_contacts.end(),
                                                                             [&](const Contact& contact){return contact.dbID() == data.dbID();})));
    changeContactData(modelIndex, data);
}


bool ContactsModel::updateContacts()
{
    bool requestResult {m_contactsWorker.requestBrowseContacts()};

#ifdef DEBUG_OUTPUT
    for(auto& contact : m_contacts) {
        qDebug() <<  "ID: " << contact.dbID() << " "
                 <<  "Name: " << contact.firstName() << " "
                 <<  "Surname: " << contact.secondName() << " "
                 <<  "PhoneNumber: " << contact.phone();
    }
    qDebug() << "In function ContactsModel::updateContacts() requestResult:"<< requestResult;
#endif

    return requestResult;
}
