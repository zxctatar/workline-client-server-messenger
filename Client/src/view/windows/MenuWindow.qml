pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../resources"
import "../customwidgets/widgets"
import "../windowpages/menumainpage"
import "../windowpages/menuprofilepage"
import "../windowpages/menuapplicationpage"
import "../windowpages/selectuserspage"

Popup {
    id: menuWindow
    width: Sizes.maxMenuWindowWidth // 230
    height: Sizes.maxMenuWindowHeight // 550
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    signal deleteAll()

    property var controller // topBarController topBar.qml

    property var notificationManager // topBar notificationManager

    property int serverId: -1
    property int serverRole: -1
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

        function onSetServerId(serverId) {
            menuWindow.serverId = serverId
        }

        function onSelectedServerDeletedSignal() {
            menuWindow.serverSelected = false

            if(stackView.currentItem.objectName == "MenuAddUserOnServer")
            {
                stackView.pop()
                menuWindow.width = Sizes.maxMenuWindowWidth // 230
                menuWindow.height = Sizes.maxMenuWindowHeight // 550
            }

            if(stackView.currentItem.objectName == "MenuConfigureAdmin")
            {
                stackView.pop()
                menuWindow.width = Sizes.maxMenuWindowWidth // 230
                menuWindow.height = Sizes.maxMenuWindowHeight // 550
            }
        }

        function onSetServerRoleSignal(roleId) {
            menuWindow.serverRole = roleId

            if(roleId == 0 && menuWindow.serverSelected == true) // none
            {
                menuWindow.controller.accessToServerDenied(menuWindow.serverId)
            }
            else if(roleId == 1) // user
            {
                if(stackView.currentItem.objectName == "MenuAddUserOnServer")
                {
                    stackView.pop()
                    menuWindow.width = Sizes.maxMenuWindowWidth // 230
                    menuWindow.height = Sizes.maxMenuWindowHeight // 550
                }
            }
            else if(roleId == 2) // admin
            {

            }
        }
    }

    Component.onCompleted: {
        menuWindow.controller.checkServerSelected()
        menuWindow.controller.getServerId()
        menuWindow.controller.getServerRole()
        menuWindow.controller.getUserRole()
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
        radius: Sizes.windowsRadius // 26
        anchors.fill: parent
        anchors.margins: -2
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

                serverRole: menuWindow.serverRole
                userRole: menuWindow.userRole
                serverSelected: menuWindow.serverSelected

                onProfileButtonClicked: {
                    menuWindow.width = Sizes.maxMenuProfilePageWidth // 475
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
                        serverId: menuWindow.serverId,
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
                            if(typeof menuWindow !== 'undefined' && menuWindow) {
                                menuWindow.controller.deleteAddUserOnServerController()
                            }
                        })
                    }
                }

                onConfigureAdminButtonClicked: {
                    menuWindow.width = Sizes.maxMenuConfigureAdminPageWidth // 475
                    menuWindow.height = Sizes.maxMenuConfigureAdminPageHeight // 550

                    var page = stackView.push(Qt.resolvedUrl("qrc:/view/windowpages/menuconfigureadminpage/MenuConfigureAdminPage.qml"), {
                        width: parent.width,
                        height: parent.height,
                        serverId: menuWindow.serverId,
                        controller: menuWindow.controller.configureAdminController,
                        notificationManager: menuWindow.notificationManager,
                    })

                    if(page) {
                        page.backButtonClicked.connect(function(){
                            stackView.pop()
                            menuWindow.width = Sizes.maxMenuWindowWidth // 230
                            menuWindow.height = Sizes.maxMenuWindowHeight // 550
                        })

                        page.deleteController.connect(function(){
                            if(typeof menuWindow !== 'undefined' && menuWindow) {
                                menuWindow.controller.deleteConfigureAdminController()
                            }
                        })
                    }
                }

                onCreateGroupChatClicked: {
                    menuWindow.width = Sizes.maxMenuCreateGroupChatPageWidth // 475
                    menuWindow.height = Sizes.maxMenuCreateGroupChatPageHeight // 340

                    var page = stackView.push(Qt.resolvedUrl("qrc:/view/windowpages/menucreategroupchatpage/MenuCreateGroupChatPage.qml"), {
                        width: parent.width,
                        height: parent.height,
                        controller: menuWindow.controller.createGroupChatController
                    })

                    if(page) {
                        var selectUsersPage = null

                        page.backButtonClicked.connect(function() {
                            stackView.pop()

                            if(selectUsersPage)
                            {
                                selectUsersPage.destroy()
                                selectUsersPage = null
                            }

                            menuWindow.width = Sizes.maxMenuWindowWidth // 230
                            menuWindow.height = Sizes.maxMenuWindowHeight // 550
                        })

                        page.deleteController.connect(function() {
                            if(typeof menuWindow !== "undefined" && menuWindow)
                            {
                                menuWindow.controller.deleteCreateGroupChatController()
                            }
                        })

                        page.nextButtonClicked.connect(function() {
                            menuWindow.width = Sizes.maxSelectUsersPageWidth // 400
                            menuWindow.height = Sizes.maxSelectUsersPageHeight // 550

                            if(!selectUsersPage)
                            {
                                var component = Qt.createComponent("qrc:/view/windowpages/selectuserspage/SelectUsersPage.qml")

                                if(component.status == Component.Ready)
                                {
                                    selectUsersPage = component.createObject(stackView, {
                                        width: parent.width,
                                        height: parent.height,
                                        controller: menuWindow.controller.createGroupChatController,
                                        notificationManager: menuWindow.notificationManager
                                    })

                                    if(selectUsersPage)
                                    {
                                        selectUsersPage.backButtonClicked.connect(function() {
                                            menuWindow.width = Sizes.maxMenuCreateGroupChatPageWidth // 475
                                            menuWindow.height = Sizes.maxMenuCreateGroupChatPageHeight // 270
                                            stackView.pop()
                                        })

                                        selectUsersPage.groupCreated.connect(function () {
                                            menuWindow.width = Sizes.maxMenuWindowWidth // 230
                                            menuWindow.height = Sizes.maxMenuWindowHeight // 550
                                            stackView.pop()
                                            stackView.pop()
                                        })
                                    }
                                }
                            }

                            stackView.push(selectUsersPage)

                        })
                    }
                }
                onCreateTaskClicked: {
                    menuWindow.width = 475
                    menuWindow.height = 550

                    var page = stackView.push(Qt.resolvedUrl("qrc:/view/windowpages/menucreatetaskpage/MenuCreateTaskPage.qml"),{
                        width: parent.width,
                        height: parent.height
                    })

                    if(page)
                    {
                        page.backButtonClicked.connect(function() {
                            menuWindow.width = Sizes.maxMenuWindowWidth // 230
                            menuWindow.height = Sizes.maxMenuWindowHeight // 550
                            stackView.pop()
                        })
                    }
                }
                onCheckTasksClicked: {

                }
            }
        }
    }
}
