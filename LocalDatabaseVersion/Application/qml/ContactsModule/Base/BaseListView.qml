import QtQuick 2.15
import QtQuick.Controls 2.15

ListView {
    spacing: 2
    section.criteria: ViewSection.FirstCharacter
    section.property: "name"

}