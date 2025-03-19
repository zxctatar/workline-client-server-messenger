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

    property var controller // topBarController topBar.qml

    property var notificationManager // topBar notificationManager

    property string userRole

    property string firstName
    property string lastName
    property string middleName
    property string email
    property string phoneNumber

    Connections {
        target: menuWindow.controller

        function onSetUserRoleSignal(message) {
            menuWindow.userRole = message
        }

        function onSetUserDataSignal(firstname, lastname, middlename, email, phoneNumber) {
            menuWindow.firstName = firstname
            menuWindow.lastName = lastname
            menuWindow.middleName = middlename
            menuWindow.email = email
            menuWindow.phoneNumber = phoneNumber
        }
    }

    Component.onCompleted: {
        menuWindow.controller.getUserRole()
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

                onProfileButtonClicked: {
                    menuWindow.controller.getUserData()

                    menuWindow.width = Sizes.maxMenuProfilePageWidth // 300
                    menuWindow.height = Sizes.maxMenuProfilePageHeight // 550

                    stackView.push(menuProfilePage)
                }

                onApplicationButtonClicked: {
                    menuWindow.width = Sizes.maxMenuApplicationPageWidth // 475
                    menuWindow.height = Sizes.maxMenuApplicationPageHeight // 550

                    stackView.push(menuApplicationPage)
                }
            }
        }
    }

    Component {
        id: menuProfilePage

        Item {
            width: stackView.width
            height: stackView.height

            MenuProfilePage {
                width: parent.width
                height: parent.height

                firstName: menuWindow.firstName
                lastName: menuWindow.lastName
                middleName: menuWindow.middleName
                email: menuWindow.email
                phoneNumber: menuWindow.phoneNumber

                onBackButtonClicked: {
                    stackView.pop()
                    menuWindow.width = Sizes.maxMenuWindowWidth // 230
                    menuWindow.height = Sizes.maxMenuWindowHeight // 550
                }
            }

        }
    }

    Component {
        id: menuApplicationPage

        Item {
            width: stackView.width
            height: stackView.height

            MenuApplicationPage {
                width: parent.width
                height: parent.height

                notificationManager: menuWindow.notificationManager
                controller: menuWindow.controller.applicationPageController

                onBackButtonClicked: {
                    stackView.pop()
                    menuWindow.width = Sizes.maxMenuWindowWidth // 230
                    menuWindow.height = Sizes.maxMenuWindowHeight // 550
                }
            }

        }
    }
}
