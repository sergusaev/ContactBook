#include "contactsworker.h"
#include <QDebug>

void ContactsWorker::handleContactsRequest(QTcpSocket *socket)
{
    bool browseResult;
    std::vector<QVariant> data;
    std::tie(browseResult, data) = m_contactsHandler.requestContactsBrowse();

    if (browseResult)
    {
        QVariantList dataList;
        std::copy (std::make_move_iterator(data.begin()),
                   std::make_move_iterator(data.end()),
                   std::back_inserter(dataList));
#ifdef DEBUG_OUTPUT
//        qDebug() << "";
//        qDebug() << "In function ContactsWorker::handleContactsRequest(QTcpSocket *socket) data being sent:";
//        for(const auto& item : dataList) {
//            qDebug() << item;
//        }
#endif
        net::Package resultPackage {QVariant::fromValue(dataList),
                    net::PackageType::CONTACTS_RESPONSE};
#ifdef DEBUG_OUTPUT
//        qDebug() << "";
//        qDebug() << "In function ContactsWorker::handleContactsRequest(QTcpSocket *socket) data in outcome package:";
//        qDebug() << resultPackage.data();
#endif
        emit contactsRequestCompleted(resultPackage, socket);
    }
}

void ContactsWorker::handleAddContactRequest(const net::Package& packageData, QTcpSocket *socket)
{
    QVariantList dataList = packageData.data().toList();
    DBTypes::DBIndex index = m_contactsHandler.requestContactAddition(dataList);
    dataList.push_front(index);
    net::Package resultPackage {QVariant::fromValue(dataList), net::PackageType::ADD_CONTACT_RESPONSE};
    emit contactAdditionRequestCompleted(resultPackage, socket);
}

void ContactsWorker::handleRemoveContactRequest(const net::Package &packageData, QTcpSocket *socket)
{
    DBTypes::DBIndex index = packageData.data().toInt();
    bool removalResult = m_contactsHandler.requestContactRemoval(index);
    if(removalResult) {
        net::Package resultPackage {QVariant::fromValue(index), net::PackageType::REMOVE_CONTACT_RESPONSE};
        emit contactRemovalRequestCompleted(resultPackage, socket);
        qWarning() << "Contact removal succeed! DB index of deleted contact:" << index;
    } else {
        qCritical() << "Contact removal failed! DB index of contact failed to delete:" << index;
        return;
    }
}

void ContactsWorker::handleUpdateContactRequest(const net::Package &packageData, QTcpSocket *socket)
{
    QVariantList dataList = packageData.data().toList();

#ifdef DEBUG_OUTPUT
    qDebug() << dataList;
#endif
    DBTypes::DBIndex index = dataList.first().toInt();
    dataList.pop_front();
    bool updatelResult = m_contactsHandler.requestContactUpdate(index, dataList);
    if(updatelResult) {
        dataList.push_front(QVariant::fromValue(index));
        net::Package resultPackage {QVariant::fromValue(dataList), net::PackageType::UPDATE_CONTACT_RESPONSE};
        emit contactRemovalRequestCompleted(resultPackage, socket);
        qWarning() << "Contact update succeed! DB index of updated contact:" << index;
    } else {
        qCritical() << "Contact removal failed! DB index of contact failed to update:" << index;
        return;
    }

}
