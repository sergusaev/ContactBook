import QtQuick 2.15
import ContactsModule.Base 1.0
import ResourceProvider 1.0
import StyleSettings 1.0
import QtQuick.Controls 2.15


BaseContactWindow  {
    id: root
    readonly property string pageType: "ContactWindow"

    property alias name: _name_text.text
    property alias surname: _surname_text.text
    property alias phoneNumber: _phone_number_text.text

    property alias nameBaseEdited: _name_base_text_edit.text
    property alias surnameBaseEdited: _surname_base_text_edit.text
    property alias phoneNumberBaseEdited: _phone_number_base_text_edit.text


    property int currentIndex: -1

    signal contactDataChanged(string _name, string _surname, string _phoneNumber, int _index)

    onContactDataChanged: {
        contactsModel.changeContactData(_name, _surname, _phoneNumber, _index)
        //        console.log(_name, _surname, _phoneNumber, _index)

    }

    ImageBubble {
        id: _contact_bubble
        width: root.height * 0.3
        height: root.height * 0.3
        anchors.top: root.top
        anchors.topMargin: height / 4
        anchors.horizontalCenter: root.horizontalCenter
        image.source: Resources.contacts.defaultContactIcon
    }

    Column {
        id: _contact_info_column
        anchors.horizontalCenter: _contact_bubble.horizontalCenter
        anchors.top: _contact_bubble.bottom
        anchors.topMargin: Style.defaultOffset
        spacing: Style.bigSpacing
        visible: true
        Row {
            spacing: Style.bigSpacing
            Column {
                spacing: Style.bigSpacing
                BaseText {id: _name_text_title; text:  qsTr("Name:"); color:Style.primaryColor; font.bold: true }
                BaseText {id: _surname_text_title; text:  qsTr("Surname:"); color:Style.primaryColor; font.bold: true}
                BaseText {id: _phone_number_text_title; text:  qsTr("Phone:") ; color:Style.primaryColor; font.bold: true}
            }
            Column {
                spacing: Style.bigSpacing
                BaseText {id: _name_text; text:  qsTr("") }
                BaseText {id: _surname_text; text:  qsTr("")}
                BaseText {id: _phone_number_text; text:  qsTr("")}
            }
        }
    }

    Column {
        id: _contact_edit_column
        visible: false
        anchors.horizontalCenter: _contact_bubble.horizontalCenter
        anchors.top: _contact_bubble.bottom
        anchors.topMargin: Style.defaultOffset
        spacing: Style.bigSpacing

        BaseTextEdit {
            id:_name_base_text_edit
            width: root.width / 1.5
            height:width / 5
            font.pointSize: 13
            color: Style.textColor
            placeholderText: qsTr("Name")

//            onTextChanged: {
//                console.log("nameBaseEdited === " + nameBaseEdited)
//                console.log("name === " + name)
//                console.log("surnameBaseEdited === " + surnameBaseEdited)
//                console.log("surname === " + surname)
//                console.log("phoneNumberBaseEdited === " + phoneNumberBaseEdited)
//                console.log("phoneNumber === " + phoneNumber)

//            }

        }
        BaseTextEdit {
            id:_surname_base_text_edit
            width: root.width / 1.5
            height:width / 5

            font.pointSize: 13
            color: Style.textColor
            placeholderText: qsTr("Surname")


        }
        BaseTextEdit {
            id:_phone_number_base_text_edit

            width: root.width / 1.5
            height:width / 5
            font.pointSize: 13
            color: Style.textColor
            placeholderText: qsTr("Phone number")

        }

    }

    Button {
        id: _delete_contact_button
        text: qsTr("Delete contact")
        contentItem: BaseText {
            text: _delete_contact_button.text
            font.bold: true
            color: _delete_contact_button.enabled
                      ? (_delete_contact_button.pressed ? Qt.darker(Style.textColor, 1.5) : Qt.darker(Style.textColor, 1.2))
                      : Qt.darker(Style.textColor, 1.5)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        width: root.width / 1.5
        height: width / 5
        anchors.horizontalCenter: root.horizontalCenter
        anchors.bottom: root.bottom
        anchors.margins: height / 2
        enabled: true
        background: Rectangle {
            color: _delete_contact_button.enabled ? (_delete_contact_button.pressed
                                                        ? Qt.darker(Style.backgroundColor, 0.25)
                                                        : Qt.darker(Style.backgroundColor, 0.2))
                                                  :  Qt.darker(Style.backgroundColor, 0.3)
            border.color: _delete_contact_button.enabled ? "gray" : Qt.darker("gray", 1.2)
            radius: 3
        }

        onClicked: {
            contactsModel.deleteContactFromQml(currentIndex)
            _stack_view.pop()
        }
        state: ""
        states:
            State{
                name: "Disabled"
                when: root.state === "AddContactState"
                PropertyChanges { target: _delete_contact_button; enabled : false }

            }



    }


    state: ""
    states: [
        State {
            name: "EditContactState"
            PropertyChanges { target: _contact_info_column; visible : false }
            PropertyChanges { target: _contact_edit_column; visible : true}
            PropertyChanges { target: _name_base_text_edit; text: name }
            PropertyChanges { target: _surname_base_text_edit; text: surname }
            PropertyChanges { target: _phone_number_base_text_edit; text: phoneNumber}


        },
        State {
            name: "AddContactState"
            PropertyChanges { target: _contact_info_column; visible : false }
            PropertyChanges { target: _contact_edit_column; visible : true}
            PropertyChanges { target: _name_base_text_edit; text: "" }
            PropertyChanges { target: _surname_base_text_edit; text: "" }
            PropertyChanges { target: _phone_number_base_text_edit; text: ""}

        }
    ]
}




