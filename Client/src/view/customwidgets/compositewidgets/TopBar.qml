import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"
import "../widgets"
import "../../windows"

Item {
    id: topBar

    width: Sizes.topBarWidth // 230
    height: Sizes.topBarHeight // 60

    property var controller // topBarController

    property var notificationManager // mainPage notificationManager

    Rectangle {
        anchors.fill: parent
        color: Colors.topBarBackgroundColor
    }

    MenuButton {
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            menuWindow.open()
        }
    }

    MenuWindow {
        id: menuWindow
        parent: Overlay.overlay
        anchors.centerIn: parent
        controller: topBar.controller
        notificationManager: topBar.notificationManager
    }
}
