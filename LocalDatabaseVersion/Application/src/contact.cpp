#include "contact.h"



Contact::Contact(QString newFirstName, QString newSecondName, QString newPhone, DBTypes::DBIndex newID)
    : m_dbID(newID)
    , m_firstName(std::move(newFirstName))
    , m_secondName(std::move(newSecondName))
    , m_phone(std::move(newPhone))
    {}

const QString &Contact::phone() const
{
    return m_phone;
}

void Contact::setPhone(const QString &newPhone)
{
    m_phone = newPhone;
}

DBTypes::DBIndex Contact::dbID() const
{
    return m_dbID;
}

void Contact::setDbID(DBTypes::DBIndex newDbID)
{
    m_dbID = newDbID;
}

const QString &Contact::firstName() const
{
    return m_firstName;
}

void Contact::setFirstName(const QString &newFirstName)
{
    m_firstName = newFirstName;
}

const QString &Contact::secondName() const
{
    return m_secondName;
}

void Contact::setSecondName(const QString &newSecondName)
{
    m_secondName = newSecondName;
}
