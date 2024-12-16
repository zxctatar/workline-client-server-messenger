pragma Singleton
import QtQuick 2.15

QtObject {
    readonly property bool transparentBorder : true
    readonly property int radius: 5
    readonly property color shadowColor: Qt.rgba(0,0,0,0.25)
}
