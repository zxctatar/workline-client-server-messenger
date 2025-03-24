pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../resources"
import "../customwidgets/widgets"
import "../windowpages/menumainpage"
import "../windowpages/menuprofilepage"
import "../windowpages/menuapplicationpage"

Popup {
    id: menuWindow
    width: Sizes.maxMenuWindowWidth // 230
    height: Sizes.maxMenuWindowHeight // 550
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    signal deleteAll()

    property var controller // topBarController topBar.qml

    property var notificationManager // topBar notificationManager

    property string userRole
    property bool serverSelected: false

    Connections {
        target: menuWindow.controller

        function onSetUserRoleSignal(message) {
            menuWindow.userRole = message
        }

        function onServerSelectedSignal() {
            menuWindow.serverSelected = true
        }

        function onSelectedServerDeleted() {
            menuWindow.serverSelected = false

            if(stackView.currentItem.objectName == "MenuAddUserOnServer")
            {
                stackView.pop()
                menuWindow.width = Sizes.maxMenuWindowWidth // 230
                menuWindow.height = Sizes.maxMenuWindowHeight // 550
            }
        }
    }

    Component.onCompleted: {
        menuWindow.controller.getUserRole()
        menuWindow.controller.checkServerSelected()
    }

    Component.onDestruction: {
        menuWindow.deleteAll()
    }

    onClosed: {
        stackView.clear()
        stackView.push(menuMainPage)

        menuWindow.width = Sizes.maxMenuWindowWidth // 230
        menuWindow.height = Sizes.maxMenuWindowHeight // 550
    }

    Overlay.modal: Rectangle {
        color: Qt.rgba(0, 0, 0, 0.50)
    }

    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 100 }
    }

    exit: Transition {
        NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 100 }
    }

    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
        radius: Sizes.radiusMenuWindow // 5
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: menuMainPage
        clip: true
    }

    Component {
        id: menuMainPage

        Item {
            width: stackView.width
            height: stackView.height

            MenuMainPage {
                width: parent.width
                height: parent.height

                userRole: menuWindow.userRole
                serverSelected: menuWindow.serverSelected

                onProfileButtonClicked: {
                    menuWindow.width = Sizes.maxMenuProfilePageWidth // 300
                    menuWindow.height = Sizes.maxMenuProfilePageHeight // 550

                    var page = stackView.push(Qt.resolvedUrl("qrc:/view/windowpages/menuprofilepage/MenuProfilePage.qml"), {
                        width: parent.width,
                        height: parent.height,
                        controller: menuWindow.controller.profilePageController,
                    })

                    if(page) {
                        page.backButtonClicked.connect(function(){
                            stackView.pop()
                            menuWindow.width = Sizes.maxMenuWindowWidth // 230
                            menuWindow.height = Sizes.maxMenuWindowHeight // 550
                        })
                    }
                }

                onApplicationButtonClicked: {
                    menuWindow.width = Sizes.maxMenuApplicationPageWidth // 475
                    menuWindow.height = Sizes.maxMenuApplicationPageHeight // 550

                    var page = stackView.push(Qt.resolvedUrl("qrc:/view/windowpages/menuapplicationpage/MenuApplicationPage.qml"),{
                        width: parent.width,
                        height: parent.height,
                        notificationManager: menuWindow.notificationManager,
                        controller: menuWindow.controller.applicationPageController,
                    })

                    if(page) {
                        page.backButtonClicked.connect(function(){
                            stackView.pop()
                            menuWindow.width = Sizes.maxMenuWindowWidth // 230
                            menuWindow.height = Sizes.maxMenuWindowHeight // 550
                        })

                        page.deleteController.connect(function(){
                            if(typeof menuWindow !== 'undefined' && menuWindow) {
                                menuWindow.controller.deleteApplicationPageController()
                            }
                        })
                    }
                }

                onAddUserOnServerButtonClicked: {
                    menuWindow.width = Sizes.maxMenuAddUserOnServerPageWidth // 475
                    menuWindow.height = Sizes.maxMenuAddUserOnServerPageHeight // 550

                    var page = stackView.push(Qt.resolvedUrl("qrc:/view/windowpages/menuadduseronserverpage/MenuAddUserOnServerPage.qml"), {
                        width: parent.width,
                        height: parent.height,
                        controller: menuWindow.controller.addUserController,
                        notificationManager: menuWindow.notificationManager,
                    })

                    if(page) {
                        page.backButtonClicked.connect(function(){
                            stackView.pop()
                            menuWindow.width = Sizes.maxMenuWindowWidth // 230
                            menuWindow.height = Sizes.maxMenuWindowHeight // 550
                        })

                        page.deleteController.connect(function(){
                            if(typeof meniWindow !== 'undefined' && menuWindow) {
                                menuWindow.controller.deleteAddUserOnServerController()
                            }
                        })
                    }
                }
            }
        }
    }
}
