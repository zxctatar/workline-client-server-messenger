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
        width: Sizes.maxBackButtonMenuWidth // 40
        height: Sizes.maxBackButtonMenuHeight // 40

        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 7
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 7
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            menuApplicationPage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 10
        font.pixelSize: Sizes.menuTextSizeInMenu // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Заявки"
    }

    ListView {
        id: listView
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.top: windowText.bottom
        anchors.bottom: refreshbutton.top
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: Sizes.serverTableSpacing // 10
        model: menuApplicationPage.controller ? menuApplicationPage.controller.getUnverUserModel() : null // UnverifiedUserModel
        interactive: true
        clip: true

        delegate: ApplicationObject {
            required property int id
            required property string name
            required property string imagePath

            displayName: name
            width: parent ? parent.width : undefined
            height: Sizes.maxApplicationObjectHeight
            path: imagePath

            onApproveButtonClicked: {
                menuApplicationPage.controller.approveUser(id)
            }

            onRejectButtonClicked: {
                menuApplicationPage.controller.rejectUser(id)
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
        text: "Обновить"

        onClicked: {
            menuApplicationPage.controller.refreshUnverUsers()
        }
    }
}
