#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <QAbstractListModel>
#include <vector>
#include <string>
#include "contact.h"
#include "contacts_handler.h"
#include "manipulator.h"



class ContactsModel : public QAbstractListModel
{
    Q_OBJECT


public:
    ContactsModel();

    static void registerModel(const std::string& modelName);

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = {}) const override;

    QVariant data(const QModelIndex &index = {}, int role = Qt::DisplayRole) const override;

    int currentElementIndex() const;
    void setCurrentElementIndex(int newCurrentElementIndex);

    Q_INVOKABLE void changeContactData(const QString& name, const QString& surname, const QString& phoneNumber, int index);

    void addContact(Contact contact);

    void deleteContact(int index);

    Q_INVOKABLE void addContactFromQml(const QString& name, const QString& surname, const QString& phoneNumber);

    Q_INVOKABLE void deleteContactFromQml(int index);






private:


    std::vector<Contact> m_contacts;

    ContactsHandler m_contactsHandler;

    enum ContactRoles {
        NameRole = Qt::UserRole + 1,
        SurnameRole,
        PhoneNumberRole,
        AllElementsRole
    };

    bool updateContacts();


};

#endif // CONTACTSMODEL_H
