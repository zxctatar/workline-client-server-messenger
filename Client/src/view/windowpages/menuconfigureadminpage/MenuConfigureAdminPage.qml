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
        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 25
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 20
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            configureAdminPage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 20
        font.pixelSize: Sizes.menuTextSize // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Настроить администратора"
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
        anchors.top: sep.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: refreshbutton.top
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        spacing: Sizes.objectDistance // 15
        model: configureAdminPage.controller ? configureAdminPage.controller.getUsersModel() : null // users model
        interactive: true
        clip: true

        delegate: ConfigureAdminObject {
            required property int id
            required property string name
            required property bool isServerAdmin
            required property string imagePath

            width: parent ? parent.width : undefined
            height: Sizes.objectHeight // 50

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

    RefreshButton {
        id: refreshbutton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15

        onClicked: {
            configureAdminPage.controller.refreshUsers()
        }
    }
}
