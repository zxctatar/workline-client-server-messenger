import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: addUserOnServerPage

    objectName: "MenuAddUserOnServer"

    property var controller // AddUserOnServerController MenuWindow.qml

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

    BackButton {
        id: backButton
        width: Sizes.maxBackButtonMenuWidth // 40
        height: Sizes.maxBackButtonMenuHeight // 40

        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 7
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 7
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            addUserOnServerPage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 10
        font.pixelSize: Sizes.menuTextSizeInMenu // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Добавить пользователя"
    }

    ListView {
        anchors.top: windowText.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: refreshbutton.top
        anchors.topMargin: 10
        spacing: 10
        model: addUserOnServerPage.controller ? addUserOnServerPage.controller.getCandidateUserModel() : null // candidate user model
        interactive: true
        clip: true

        delegate: CandidateUserObject {
            required property int id
            required property string name

            displayName: name
            width: parent ? parent.width : undefined
            height: Sizes.maxCandidateUserObjectHeight // 50
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
            addUserOnServerPage.controller.refreshCandidateUsers()
        }
    }
}
