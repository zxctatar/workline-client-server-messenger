pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"
import "../widgets"
import "../../windows"

Item {
    id: serverTable

    property var controller // serverTableController

    property string userRole

    property var notificationManager // mainPage notificationManager

    width: Sizes.maxServerTableWidth // 78

    Connections {
        target: serverTable.controller

        function onSetUserRoleSignal(message) {
            serverTable.userRole = message
        }

        function onServerAdded() {
            addServerWindow.clearInputFields()
            addServerWindow.close()
        }

        function onServerNameExistsSignal() {
            addServerWindow.serverNameExists()
        }

        function onErrorCreateServerSignal() {
            addServerWindow.errorCreateServer()
        }
    }

    Component.onCompleted: {
        serverTable.controller.getUserRole()
        serverTable.controller.getServers()
    }

    Rectangle {
        id: backList
        anchors.fill: parent
        color: Colors.serverTableBackgroundColor

        ListView {
            id: listView
            anchors.fill: backList
            spacing: Sizes.serverTableSpacing // 10
            model: serverTable.controller.getServerModel()
            interactive: true
            clip: true

            delegate: ServerObject {
                required property int id
                required property string name

                anchors.horizontalCenter: parent ? parent.horizontalCenter : undefined
                text: name
            }

            footer: Item {
                width: parent.width
                height: 60

                AddServerButton {
                    id: addServerButton
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    visible: serverTable.userRole == "admin" ? true : false

                    onClicked: {
                        addServerWindow.open()
                    }
                }
            }

            AddServerWindow {
                id: addServerWindow
                parent: Overlay.overlay
                anchors.centerIn: parent
                notificationManager: serverTable.notificationManager

                onAddServerSignal: function(serverName, serverDescription) {
                    serverTable.controller.preparingAddServerRequest(serverName, serverDescription)
                }
            }
        }
    }
}

