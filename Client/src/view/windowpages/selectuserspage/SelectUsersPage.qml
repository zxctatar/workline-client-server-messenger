pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: selectUsersPage

    signal backButtonClicked()
    signal groupCreated()

    property var controller // CreateGroupChatController
    property var notificationManager

    background: Rectangle {
        color: "#D3E3F1"
    }

    Component.onCompleted: {
        selectUsersPage.controller.getUsers()
    }

    Connections {
        target: selectUsersPage.controller

        function onNoUsersSignal() {
            selectUsersPage.notificationManager.showNotificationManager("Добавьте пользователей.")
        }

        function onCodeErrorSignal() {
            selectUsersPage.notificationManager.showNotificationManager("Ошибка на сервере.")
        }

        function onCodeAccessDeniedSignal() {
            selectUsersPage.notificationManager.showNotificationManager("Доступ запрещён.")
        }

        function conCodeGroupNameExistsSignal() {
            selectUsersPage.notificationManager.showNotificationManager("Название группы занято.")
        }

        function onCodeGroupCreatedSignal() {
            selectUsersPage.groupCreated()
        }
    }

    BackButton {
        id: backButton
        width: Sizes.maxBackButtonMenuWidth // 40
        height: Sizes.maxBackButtonMenuHeight // 40

        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 7
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 7
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            selectUsersPage.backButtonClicked()
        }
    }

    ListView {
        id: listView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: refreshbutton.top
        anchors.top: backButton.bottom
        clip: true
        spacing: 10
        model: selectUsersPage.controller.getUsersModel()

        delegate: AddUsersObject {
            required property int id
            required property string name
            required property string imagePath

            displayName: name
            path: imagePath
            width: parent.width
            height: 40

            onAddUserSignal: {
                selectUsersPage.controller.addUser(id)
                isSelected = true
            }
            onRemoveUserSignal: {
                selectUsersPage.controller.removeUser(id)
                isSelected = false
            }
        }
    }

    MyButton {
        id: refreshbutton
        width: Sizes.maxMenuApplicaionPageRefreshButtonWidth // 100
        height: Sizes.maxMenuApplicaionPageRefreshButtonHeight // 50
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Sizes.menuTextSizeInWidgets // 16
        anchors.bottom: parent.bottom
        text: "Готово"

        onClicked: {
            selectUsersPage.controller.createChat()
        }
    }
}
