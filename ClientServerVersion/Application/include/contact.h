#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QObject>
#include <dbtypes.h>

class Contact
{


public:
    Contact() = default;

    Contact(QString newFirstName, QString newSecondName, QString newPhone, DBTypes::DBIndex newID = -1);

    Contact(const Contact& other);

    Contact(Contact&& other);



    const QString &firstName() const;
    void setFirstName(const QString &newFirstName);

    const QString &secondName() const;
    void setSecondName(const QString &newSecondName);

    const QString &phone() const;
    void setPhone(const QString &newPhone);

    DBTypes::DBIndex dbID() const;
    void setDbID(DBTypes::DBIndex newDbID);

    bool operator==(const Contact& other) const{
        return (other.firstName() == firstName()
                && other.secondName() == secondName()
                && other.phone() == phone());
    }

    Contact& operator=(const Contact& other) {
        if(*this == other) {
            return *this;
        }

        m_dbID = other.m_dbID;
        m_firstName = other.m_firstName;
        m_secondName = other.m_secondName;
        m_phone = other.m_phone;
        return *this;
    }


private:
    DBTypes::DBIndex m_dbID;
    QString m_firstName;
    QString m_secondName;
    QString m_phone;
};

Q_DECLARE_METATYPE(Contact)

#endif // CONTACT_H
