pragma Singleton
import QtQuick 2.15

QtObject {
    // toolBar
    readonly property color toolBarColor: "#4EABFD"

    // кнопки
    readonly property color toolBarDefaultButtonColor: "#4EABFD"
    readonly property color toolBarHoverButtonColor: "#1E88E5"
    readonly property color toolBarHoverCloseButtonColor: "#FF0000"


    //DropShadow
    readonly property color dropShadowToolBarColor: Qt.rgba(0,0,0,0.05)
}
