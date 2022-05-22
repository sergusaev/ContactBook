import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import StyleSettings 1.0
import ContactsModule.Impl 1.0
import ResourceProvider 1.0
import QtGraphicalEffects 1.15

ApplicationWindow {
    id: root
    width: 350
    height: 760
    visible: true
    title: qsTr("Contact book")

    header: ToolBar {
        id: _toolbar
        height: root.height / 20
        background: Rectangle {
            color: Qt.darker(Style.backgroundColor, 0.22)
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 2
                color: "transparent"
                border.color: "gray"
            }
        }
        RowLayout {
            anchors.fill: parent
            ToolButton {
                id: _left_toolbar_button
                Layout.preferredWidth: 40
                Layout.preferredHeight:  _toolbar.height
                icon.source: Resources.backIcon.backIconToolbar
                icon.color: _left_toolbar_button.enabled
                            ? (_left_toolbar_button.pressed ? Qt.darker(Style.textColor, 1.5) : Qt.darker(Style.textColor, 1.2))
                            : Qt.darker(Style.textColor, 1.5)



                background: Rectangle {
                    id:_left_toolbar_button_background
                    color: _left_toolbar_button.pressed ? Qt.darker(Style.backgroundColor, 0.27) : Qt.darker(Style.backgroundColor, 0.22)
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: "transparent"
                        border.color: _left_toolbar_button.pressed ? Qt.darker("gray", 1.3) : "gray"
                    }
                }

                onClicked: {
                    if(_stack_view.depth > 1){
                        close.accepted = false
                        _stack_view.pop();
                    }else{
                        return;
                    }
                }
            }


            Label {
                text: _stack_view.currentItem.pageType === "ContactsView" ? qsTr("Contacts") : ""
                color: Style.textColor
                font.pointSize: 13
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true

            }


            ToolButton {
                id: _right_toolbar_button
                icon.source:Resources.addIcon.addIconToolbar
                icon.color: _right_toolbar_button.enabled
                            ? (_right_toolbar_button.pressed ? Qt.darker(Style.textColor, 1.5) : Qt.darker(Style.textColor, 1.2))
                            : Qt.darker(Style.textColor, 1.5)

                Layout.preferredWidth:  40
                Layout.preferredHeight:   _toolbar.height
                enabled: true
                background: Rectangle {
                    id: _right_toolbar_button_background
                    color: _right_toolbar_button.pressed ? Qt.darker(Style.backgroundColor, 0.27) : Qt.darker(Style.backgroundColor, 0.22)
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: "transparent"
                        border.color: _right_toolbar_button.pressed ? Qt.darker("gray", 1.3) : "gray"
                    }
                }

                state: "Add"
                states: [
                    State {
                        name: "Add"
                        when: _stack_view.currentItem.pageType === "ContactsView"
                    },
                    State {
                        name: "Edit"
                        when: _stack_view.currentItem.pageType === "ContactWindow" && _stack_view.currentItem.state === ""
                        PropertyChanges {
                            target: _right_toolbar_button
                            icon.source:Resources.editIcon.editIconToolbar
                        }
                    },
                    State {
                        name: "Save"
                        when: _stack_view.currentItem.pageType === "ContactWindow" && _stack_view.currentItem.state !== ""
                        PropertyChanges {
                            target: _right_toolbar_button
                            icon.source:Resources.saveIcon.saveIconToolbar
                            enabled: (_stack_view.currentItem.state === "AddContactState"
                                     && (_stack_view.currentItem.nameBaseEdited === ""
                                         && _stack_view.currentItem.surnameBaseEdited === ""
                                         && _stack_view.currentItem.phoneNumberBaseEdited === ""))
                                    || (_stack_view.currentItem.state === "EditContactState"
                                     && (_stack_view.currentItem.nameBaseEdited === _stack_view.currentItem.name
                                         && _stack_view.currentItem.surnameBaseEdited === _stack_view.currentItem.surname
                                         && _stack_view.currentItem.phoneNumberBaseEdited === _stack_view.currentItem.phoneNumber)) ? false : true
                        }
                    }

                ]


                onClicked: {


                    if (state === "Add") {
                        _stack_view.push(_contact_window_stack_page, {"state" : "AddContactState", "currentIndex" : -1})

                    } else if (state === "Edit") {
                        _stack_view.currentItem.state = "EditContactState"
                    } else if(state === "Save") {
                        if(_stack_view.currentItem.state === "EditContactState") {
                            _stack_view.currentItem.contactDataChanged(_stack_view.currentItem.nameBaseEdited,
                                                                       _stack_view.currentItem.surnameBaseEdited,
                                                                       _stack_view.currentItem.phoneNumberBaseEdited,
                                                                       _stack_view.currentItem.currentIndex)
                            _stack_view.pop()
                        } else {
                            contactsModel.addContactFromQml(_stack_view.currentItem.nameBaseEdited,
                                                            _stack_view.currentItem.surnameBaseEdited,
                                                            _stack_view.currentItem.phoneNumberBaseEdited)
                            _stack_view.pop()
                        }
                    }
//                    console.log("pageType: " + _stack_view.currentItem.pageType)
//                    console.log("right toolbar button state: " + _right_toolbar_button.state)
//                    console.log("state: " + _stack_view.currentItem.state)
//                    console.log("nameBaseEdited: " + _stack_view.currentItem.nameBaseEdited)
//                    console.log("name: " + _stack_view.currentItem.name)
//                    console.log("surnameBaseEdited: " + _stack_view.currentItem.surnameBaseEdited)
//                    console.log("surname: " + _stack_view.currentItem.surname)
//                    console.log("phoneNumberBaseEdited: " + _stack_view.currentItem.phoneNumberBaseEdited)
//                    console.log("phoneNumber: " + _stack_view.currentItem.phoneNumber)
                }
            }
        }
    }



    StackView {
        id: _stack_view
        anchors.fill:parent
        initialItem: _contacts_view_stack_page
    }

    Component {
        id: _contacts_view_stack_page
        ContactsView {
        }
    }

    Component {
        id:  _contact_window_stack_page
        ContactWindow {
        }
    }
    onClosing: {
        if(_stack_view.depth > 1){
            close.accepted = false
            _stack_view.pop();
        }else{
            return;
        }


    }
}
