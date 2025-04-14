import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
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

    ColumnLayout {
        id: layout

        width: 230

        Layout.maximumWidth: 400
        Layout.minimumWidth: 100

        anchors.top: parent.top
        anchors.left: table.right
        anchors.bottom: parent.bottom
        spacing: 0

        TopBar {
            id: topBar
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            controller: mainPage.mainController.topBarController
            notificationManager: mainPage.notificationManager
        }

        ChatsBar {
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width
            Layout.alignment: Qt.AlignTop
            controller: mainPage.mainController.chatsBarController
        }
    }

    ChatHistory {
        controller: mainPage.mainController.chatHistoryController
        notificationManager: mainPage.notificationManager

        anchors.left: layout.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    MouseArea {
        id: mouseArea

        width: 5

        anchors.left: layout.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        hoverEnabled: true

        cursorShape: Qt.SizeHorCursor

        onPressed: {
            drag.target = layout
            drag.axis = Drag.XAxis
        }

        onPositionChanged: {
            if(drag.active) {
                const newWidth = Math.max(
                    100, Math.min(
                        400,
                        layout.width + mouseX
                        )
                )
                layout.width = newWidth
            }
        }
    }
}
