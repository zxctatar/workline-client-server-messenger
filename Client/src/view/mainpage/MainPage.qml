import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../resources"
import "../widgets"

Page {
    id: mainPage

    property var mainController // MainController

    property var notificationManager // mainWindow notificationManager

    background: Rectangle {
        color: Colors.windowBackgroundColor
    }

    ServerTable {
        id: table
        notificationManager: mainPage.notificationManager
        controller: mainPage.mainController.serverTableController
        anchors.left: parent.left
        width: 78
        height: parent.height
    }
}
