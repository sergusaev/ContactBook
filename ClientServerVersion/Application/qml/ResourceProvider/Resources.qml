pragma Singleton
import QtQuick 2.15

Item {
    property alias contacts: _contacts
    property alias backIcon: _back_icon_toolbar
    property alias addIcon: _add_icon_toolbar
    property alias editIcon: _edit_icon_toolbar
    property alias saveIcon: _save_icon_toolbar


    QtObject {
        id: _contacts
        readonly property string defaultContactIcon : "qrc:/qml/resources/default_contact_icon.svg"

    }
    QtObject {
        id: _back_icon_toolbar
        readonly property string backIconToolbar : "qrc:/qml/resources/back_icon_toolbar.svg"

    }

    QtObject {
        id: _add_icon_toolbar
        readonly property string addIconToolbar : "qrc:/qml/resources/add_icon_toolbar.svg"

    }
    QtObject {
        id: _edit_icon_toolbar
        readonly property string editIconToolbar : "qrc:/qml/resources/edit_icon_toolbar.svg"

    }
    QtObject {
        id: _save_icon_toolbar
        readonly property string saveIconToolbar : "qrc:/qml/resources/save_icon_toolbar.svg"

    }

}
