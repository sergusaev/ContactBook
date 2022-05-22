import QtQuick 2.15
import ContactsModule.Base 1.0
import QtQuick.Controls 2.15
import StyleSettings 1.0
import QtGraphicalEffects 1.15
import ResourceProvider 1.0


Rectangle {
    id: root
    readonly property string pageType: "ContactsView"

    BaseListView {
        id: _contacts_view
        anchors.fill: parent
        model: contactsModel
        delegate: ContactDelegate {
            width: root.width
            height: root.height / 10
            onClicked: {
                _stack_view.push(_contact_window_stack_page,
                                 {"name": name,
                                  "surname": surname,
                                  "phoneNumber": phoneNumber,
                                  "nameBaseEdited" : "",
                                  "surnameBaseEdited" : "",
                                  "phoneNumberBaseEdited" : "",
                                  "currentIndex": index})
//                console.log("pageType: " + _stack_view.currentItem.pageType)
//                console.log("state: " + _stack_view.currentItem.state)
//                console.log("name: " + _stack_view.currentItem.name)
//                console.log("nameBaseEdited: " + _stack_view.currentItem.nameBaseEdited)
//                console.log("surname: " + _stack_view.currentItem.surname)
//                console.log("surnameBaseEdited: " + _stack_view.currentItem.surnameBaseEdited)
//                console.log("phoneNumber: " + _stack_view.currentItem.phoneNumber)
//                console.log("phoneNumberBaseEdited: " + _stack_view.currentItem.phoneNumberBaseEdited)
//                console.log("currentIndex: " + _stack_view.currentItem.currentIndex)
            }
        }
    }
}
