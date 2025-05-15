pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: addUserOnServerPage

    objectName: "MenuAddUserOnServer"

    property var controller // AddUserOnServerController MenuWindow.qml
    property var notificationManager // notificationManager MenuWindow.qml

    property int serverId: -1

    signal backButtonClicked()

    signal deleteController()

    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
    }

    Component.onCompleted: {
        addUserOnServerPage.controller.getCandidateUsers()
    }

    Component.onDestruction: {
        addUserOnServerPage.deleteController()
    }

    Connections {
        target: addUserOnServerPage.controller

        function onUserNotVerifiedSignal() {
            addUserOnServerPage.notificationManager.showNotificationManager("Пользователь не подтверждён")
        }

        function onUserAlreadyAddedSignal() {
            addUserOnServerPage.notificationManager.showNotificationManager("Пользователь уже добавлен")
        }

        function onUserAddedOnServerSignal() {
            addUserOnServerPage.notificationManager.showNotificationManager("Пользователь добавлен")
        }

        function onErrorSignal() {
            addUserOnServerPage.notificationManager.showNotificationManager("Ошибка на сервере")
        }
    }

    BackButton {
        id: backButton
        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 25
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 20
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            addUserOnServerPage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 20
        font.pixelSize: Sizes.menuTextSize // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Добавить пользователя"
    }

    Separator {
        id: sep
        anchors.top: windowText.bottom
        anchors.topMargin: 20
        width: parent.width - 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ListView {
        anchors.top: sep.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: refreshbutton.top
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        spacing: Sizes.objectDistance // 15
        model: addUserOnServerPage.controller ? addUserOnServerPage.controller.getCandidateUserModel() : null // candidate user model
        interactive: true
        clip: true

        delegate: CandidateUserObject {
            required property int id
            required property string name
            required property string imagePath

            displayName: name
            width: parent ? parent.width : undefined
            height: Sizes.objectHeight // 50
            path: imagePath

            onAddUserClicked: {
                addUserOnServerPage.controller.requestAddUser(id, addUserOnServerPage.serverId)
            }
        }
    }

    RefreshButton {
        id: refreshbutton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15

        onClicked: {
            addUserOnServerPage.controller.refreshCandidateUsers()
        }
    }
}
