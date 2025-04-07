import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: configureAdminPage

    property var controller // C MenuWindow.qml
    property var notificationManager // notificationManager MenuWindow.qml

    property int serverId

    signal backButtonClicked()

    signal deleteController()

    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
    }

    Component.onCompleted: {
        configureAdminPage.controller.getServerId()
        configureAdminPage.controller.getUsersOnServer()
    }

    Component.onDestruction: {
        configureAdminPage.deleteController()
    }

    Connections {
        target: configureAdminPage.controller

        function onSetServerIdSignal(serverId) {
            configureAdminPage.serverId = serverId
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

    ListModel {
        id: modell
        ListElement {name: "123"}
        ListElement {name: "123"}
        ListElement {name: "123"}
        ListElement {name: "123"}
        ListElement {name: "123"}
        ListElement {name: "123"}
    }

    ListView {
        anchors.top: windowText.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: refreshbutton.top
        anchors.topMargin: 10
        spacing: 10
        model: modell //configureAdminPage.controller ? configureAdminPage.controller.getCandidateUserModel() : null // candidate user model
        interactive: true
        clip: true

        delegate: ConfigureAdminObject {
            width: parent ? parent.width : undefined
            height: 50

            displayName: "Кнутов М.В."
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
