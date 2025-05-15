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

    property var currentIndex: -1

    width: Sizes.maxServerTableWidth // 78

    Connections {
        target: serverTable.controller

        function onSetUserRoleSignal(message) {
            serverTable.userRole = message
        }

        function onMyServerAddedSignal() {
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
            spacing: Sizes.serverTableSpacing // 15
            model: serverTable.controller.getServerModel() // serverModel
            interactive: true
            clip: true

            boundsBehavior: Flickable.StopAtBounds

            header: Item {
                width: 1
                height: 10
            }

            delegate: ServerObject {
                id: serverObject

                required property int id
                required property string name
                required property string fullName
                required property string description
                required property string path

                serverId: id

                isAdmin: serverTable.userRole == "admin" ? true : false
                selected: serverTable.currentIndex == serverId ? true : false

                anchors.horizontalCenter: parent ? parent.horizontalCenter : undefined
                text: path == "" ? name : ""
                imagePath: path

                onClicked: {
                    serverTable.currentIndex = id
                    serverTable.controller.setServerData(id, fullName, description)
                    serverTable.controller.serverSelected(id)
                }

                onDeleteServerClicked:(serverId) => {
                    serverTable.controller.deleteServer(serverId)
                }
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

                onAddServerSignal: function(encodedFilePath, serverName, serverDescription) {
                    serverTable.controller.preparingAddServerRequest(encodedFilePath, serverName, serverDescription)
                }
            }
        }
    }
}

