pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../resources"
import "windows"

Item {
    id: serverTable

    property var controller // serverTableController

    property string userRole

    property var notificationManager // mainPage notificationManager

    Connections {
        target: serverTable.controller

        function onSetUserRoleSignal(message) {
            serverTable.userRole = message
        }

        function onAddNewServerSignal(message1, message2) {
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
        color: "#0D497D"

        ListView {
            id: listView
            anchors.fill: backList
            spacing: 10
            model: serverTable.controller.getServerModel()
            interactive: true
            clip: true

            delegate: Button {
                width: 50
                height: 50
                anchors.horizontalCenter: parent ? parent.horizontalCenter : undefined

                background: Rectangle {
                    color: "red"
                    border.color: "black"
                    radius: 10
                }

                Image {
                    source: "qrc:/resources/img/passwordOn.svg"
                }

                onClicked: {
                    console.log(contentItem)
                }
            }

            footer: Item {
                width: parent.width
                height: 60

                AddServerButton {
                    id: addServerButton
                    width: 50
                    height: 50
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

