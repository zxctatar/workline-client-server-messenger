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
        color: Colors.menuWindowBackgroundColor
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

        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 25
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 20
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            selectUsersPage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 20
        font.pixelSize: Sizes.menuTextSize // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Выбор пользователей"
    }

    Separator {
        id: sep
        anchors.top: windowText.bottom
        anchors.topMargin: 20
        width: parent.width - 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ListView {
        id: listView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: doneButton.top
        anchors.top: sep.bottom
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        clip: true
        spacing: 15
        model: selectUsersPage.controller.getUsersModel()

        delegate: AddUsersObject {
            required property int id
            required property string name
            required property string imagePath

            displayName: name
            path: imagePath
            width: parent.width
            height: Sizes.objectHeight // 50

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
        id: doneButton
        width: Sizes.doneButtonWidth // 100
        height: Sizes.doneButtonHeight // 50
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Sizes.standartTextSize // 16
        anchors.bottom: parent.bottom
        text: "Готово"

        onClicked: {
            selectUsersPage.controller.createChat()
        }
    }
}
