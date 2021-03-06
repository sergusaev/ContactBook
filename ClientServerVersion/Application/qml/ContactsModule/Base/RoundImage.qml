import QtQuick 2.15
import QtGraphicalEffects 1.15

Image {
    id: root
    property bool rounded: true

    layer.enabled: rounded
    layer.effect: OpacityMask {
        maskSource: Item {
            width: root.width
            height: root.height
            Rectangle {
                anchors.centerIn: parent
                anchors.fill: parent
                radius: Math.min(width, height) / 2
            }
        }
    }
}
