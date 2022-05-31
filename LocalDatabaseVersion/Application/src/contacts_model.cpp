#include "contacts_model.h"
#include <QQmlEngine>
#include <QDebug>

ContactsModel::ContactsModel()
{
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


void ContactsModel::changeContactData(const QString &name, const QString &surname, const QString &phoneNumber, int index)
{
    if(index < 0 || index > rowCount()) {
        return ;
    }
//    Contact oldContact  {m_contacts[index].firstName(), m_contacts[index].secondName(), m_contacts[index].phone()};
    m_contacts[index].setFirstName(name);
    m_contacts[index].setSecondName(surname);
    m_contacts[index].setPhone(phoneNumber);
    Contact updatedContact  {m_contacts[index].firstName(), m_contacts[index].secondName(), m_contacts[index].phone()};
    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
    m_contactsHandler.updateContact(m_contacts[index].dbID(), updatedContact);
    qDebug() << "In function ContactsModel::changeContactData(<args>) new data: " << name << surname << phoneNumber << "\n";
    qDebug() << "In function ContactsModel::changeContactData(<args>) ID of contact to update: " <<m_contacts[index].dbID() << "\n";
}

void ContactsModel::addContact(Contact contact)
{
    DBTypes::DBIndex index = m_contactsHandler.addContact(contact);
    if(index == -1) {
        qDebug() << "Failed to insert new contact into database" << "\n";
        return;
    }
    qDebug() << "New contact has index " << index << " in database" << "\n";
    contact.setDbID(index);
    beginInsertRows(QModelIndex(),rowCount(), rowCount());
    m_contacts.push_back(contact);
    for(const auto& contact : m_contacts) {
        qDebug() <<  "ID: " << contact.dbID() << " "
                 <<  "Name: " << contact.firstName() << " "
                 <<  "Surname: " << contact.secondName() << " "
                 <<  "PhoneNumber: " << contact.phone() << "\n";
    }
    endInsertRows();
}

void ContactsModel::deleteContact(int index)
{
    if(index < 0 || index > rowCount()) {
        return ;
    }
    beginRemoveRows(QModelIndex(),index, index);
    Contact contact = m_contacts[index];
    m_contacts.erase(m_contacts.begin() + index);
    endRemoveRows();
    m_contactsHandler.removeContact(index);
    for(auto& contact : m_contacts) {
        qDebug() <<  "ID: " << contact.dbID() << " "
                 <<  "Name: " << contact.firstName() << " "
                 <<  "Surname: " << contact.secondName() << " "
                 <<  "PhoneNumber: " << contact.phone() << "\n";
    }


}

void ContactsModel::addContactFromQml(const QString &name, const QString &surname, const QString &phoneNumber)
{

    addContact({name, surname, phoneNumber});

}

void ContactsModel::deleteContactFromQml(int index)
{
    deleteContact(index);
}



bool ContactsModel::updateContacts()
{
    bool requestResult {false};
    std::vector<Contact> contactsResult;
    std::tie(requestResult, contactsResult) = m_contactsHandler.requestContactsBrowse();
    if (requestResult) {
        m_contacts.swap(contactsResult);
        emit dataChanged(createIndex(0,0), createIndex(m_contacts.size(), 0));
    }
    for(auto& contact : m_contacts) {
        qDebug() <<  "ID: " << contact.dbID() << " "
                 <<  "Name: " << contact.firstName() << " "
                 <<  "Surname: " << contact.secondName() << " "
                 <<  "PhoneNumber: " << contact.phone() << "\n";
    }

    return requestResult;
}
