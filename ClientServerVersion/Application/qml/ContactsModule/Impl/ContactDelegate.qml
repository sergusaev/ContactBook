import QtQuick 2.15
import ContactsModule.Base 1.0
import ResourceProvider 1.0
import StyleSettings 1.0
import QtGraphicalEffects 1.15

BaseListDelegate {
    id: root

    ImageBubble {
        id: _contactBubble
        width: root.height * 0.9
        height: root.height * 0.9
        anchors.left: root.left
        anchors.verticalCenter: root.verticalCenter
        anchors.margins: width / 20
        image.source: Resources.contacts.defaultContactIcon
    }

    DropShadow {
        id:_contactBubble_shadow
        anchors.fill: _contactBubble
        horizontalOffset: 4
        verticalOffset: 4
        color: "black"
        source: _contactBubble
        visible: true

    }

    Column {
        anchors.verticalCenter: root.verticalCenter
        anchors.left: _contactBubble.right
        anchors.leftMargin: Style.defaultOffset

        Row {
            spacing: Style.smallSpacing
            BaseText {
                id: _delegate_text_name
                text: name
            }

            BaseText {
                id: _delegate_text_surname
                text: surname
            }

        }

        BaseText {
            id: _delegate_text_phone_number
            text: phoneNumber
            color: Style.primaryColor

        }

    }
}
