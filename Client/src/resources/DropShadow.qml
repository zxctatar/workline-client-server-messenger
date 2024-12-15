pragma Singleton
import QtQuick 2.15

QtObject {
    readonly property DropShadow shadow: {
        transparentBorder: true
        verticalOffset: 5
        radius: 5
        color: Qt.rgba(0,0,0,0.25)
    }


}
