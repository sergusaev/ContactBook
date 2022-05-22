import QtQuick 2.15
import StyleSettings 1.0
//import "../../StyleSettings" as S

Rectangle {
    id: root
    color: Style.backgroundColor
    opacity: _delegateArea.pressed ? Style.secondaryOpacity : Style.emphasisOpacity
    signal clicked()



    MouseArea {
        id: _delegateArea
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }


    }

}
