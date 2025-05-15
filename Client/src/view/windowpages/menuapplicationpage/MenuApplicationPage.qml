pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: menuApplicationPage

    property var controller // applicationPageController MenuWindow.qml

    property var notificationManager // menuWindow notificationManager

    signal backButtonClicked()
    signal deleteController()

    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
    }

    Component.onCompleted: {
        menuApplicationPage.controller.getUnverUsers()
    }

    Component.onDestruction: {
        menuApplicationPage.deleteController()
    }

    Connections {
        target: menuApplicationPage.controller

        function onApprovedSignal() {
            menuApplicationPage.notificationManager.showNotificationManager("Пользователь одобрен.")
        }

        function onRejectedSignal() {
            menuApplicationPage.notificationManager.showNotificationManager("Пользователь отклонён.")
        }

        function onAlreadyApprovedSignal() {
            menuApplicationPage.notificationManager.showNotificationManager("Пользователь уже одобрен.")
        }

        function onAlreadyRejectedSignal() {
            menuApplicationPage.notificationManager.showNotificationManager("Пользователь уже отклонён.")
        }

        function onErrorSignal() {
            menuApplicationPage.notificationManager.showNotificationManager("Ошибка на сервере.")
        }
    }

    BackButton {
        id: backButton
        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 25
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 20
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            menuApplicationPage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 20
        font.pixelSize: Sizes.menuTextSize // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Заявки"
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
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        anchors.top: sep.bottom
        anchors.bottom: refreshbutton.top
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: Sizes.objectDistance // 15
        model: menuApplicationPage.controller ? menuApplicationPage.controller.getUnverUserModel() : null // UnverifiedUserModel
        interactive: true
        clip: true

        delegate: ApplicationObject {
            required property int id
            required property string name
            required property string imagePath

            displayName: name
            width: parent ? parent.width : undefined
            height: Sizes.objectHeight
            path: imagePath

            onApproveButtonClicked: {
                menuApplicationPage.controller.approveUser(id)
            }

            onRejectButtonClicked: {
                menuApplicationPage.controller.rejectUser(id)
            }
        }
    }

    RefreshButton {
        id: refreshbutton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15

        onClicked: {
            menuApplicationPage.controller.refreshUnverUsers()
        }
    }
}
