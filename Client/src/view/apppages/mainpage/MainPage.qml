import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"
import "../../customwidgets/compositewidgets"

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
        height: parent.height
    }

    TopBar {
        anchors.left: table.right
        controller: mainPage.mainController.topBarController
        notificationManager: mainPage.notificationManager
    }
}
