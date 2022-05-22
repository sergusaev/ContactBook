import QtQuick 2.15
import QtQuick.Controls 2.15
import StyleSettings 1.0


TextField {
    id: _root
    text: qsTr("")
    color: Style.textColor
    font.pointSize: 13
    placeholderText: qsTr("")
    placeholderTextColor: "gray"

    background: Rectangle {
        id:_inner_text_field_background
        color: _root.activeFocus ? Qt.darker(Style.backgroundColor, 0.2) : Qt.darker(Style.backgroundColor, 0.35)
        border.color: "gray"
        radius: 3
    }
}

