import QtQuick 2.15
import QtGraphicalEffects 1.15
import StyleSettings 1.0

Rectangle {
    id: root
    clip: true
    property alias image: _internalImage

    RoundImage {
        id: _internalImage
        anchors.fill: parent
        anchors.centerIn: parent
        sourceSize.height: height
        sourceSize.width: width
        anchors.margins: Style.tinyOffset

    }

    radius: width / 2
    border.color: Style.primaryColor
    border.width: width / 30
    color: "transparent"

    ColorOverlay {
        anchors.fill: _internalImage
        source: root.image
        color: Style.themeInvertedColor
        antialiasing: true

    }
}
