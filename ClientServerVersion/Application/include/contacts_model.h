#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <QAbstractListModel>
#include <vector>
#include <string>
#include "contact.h"
#include "contactsworker_app.h"
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



    void changeContactData(int modelIndex, const Contact& contact);

    void addContact(const Contact& contact);

    void deleteContact(int modelIndex);

    Q_INVOKABLE void addContactFromQml(const QString& name, const QString& surname, const QString& phoneNumber);

    Q_INVOKABLE void deleteContactFromQml(int index);

    Q_INVOKABLE void changeContactDataFromQml(const QString& name, const QString& surname, const QString& phoneNumber, int index);




private slots:
    void onContactListDownloaded(const std::vector<Contact> &data);
    void onContactAdded(const Contact& data);
    void onContactRemoved(const DBTypes::DBIndex index);
    void onContactUpdated(const Contact& data);

private:


    std::vector<Contact> m_contacts;

    ContactsWorker m_contactsWorker;

    enum ContactRoles {
        NameRole = Qt::UserRole + 1,
        SurnameRole,
        PhoneNumberRole,
        AllElementsRole
    };

    bool updateContacts();


};

#endif // CONTACTSMODEL_H
