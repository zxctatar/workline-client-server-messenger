pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: configureAdminPage

    objectName: "MenuConfigureAdmin"

    property var controller // ConfigureAdminController MenuWindow.qml
    property var notificationManager // notificationManager MenuWindow.qml

    property int serverId: -1

    signal backButtonClicked()

    signal deleteController()

    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
    }

    Component.onCompleted: {
        configureAdminPage.controller.getUsersOnServer()
    }

    Component.onDestruction: {
        configureAdminPage.deleteController()
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
            configureAdminPage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 10
        font.pixelSize: Sizes.menuTextSizeInMenu // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Настроить администратора"
    }

    ListView {
        anchors.top: windowText.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: refreshbutton.top
        anchors.topMargin: 10
        spacing: 10
        model: configureAdminPage.controller ? configureAdminPage.controller.getUsersModel() : null // users model
        interactive: true
        clip: true

        delegate: ConfigureAdminObject {
            required property int id
            required property string name
            required property bool isServerAdmin
            required property string imagePath

            width: parent ? parent.width : undefined
            height: Sizes.maxConfigureAdminObjectHeight // 50

            displayName: name
            isAdmin: isServerAdmin
            path: imagePath

            onAddAdminSignal: {
                configureAdminPage.controller.sendAddAdmin(configureAdminPage.serverId, id)
            }

            onRemoveAdminSignal: {
                configureAdminPage.controller.sendRemoveAdmin(configureAdminPage.serverId, id)
            }
        }
    }

    MyButton {
        id: refreshbutton
        width: Sizes.maxMenuAddUserOnServerPageRefreshButtonWidth // 100
        height: Sizes.maxMenuAddUserOnServerPageRefreshButtonHeight // 50
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Sizes.menuTextSizeInWidgets // 16
        anchors.bottom: parent.bottom
        text: "Обновить"

        onClicked: {
            configureAdminPage.controller.refreshUsers()
        }
    }
}
