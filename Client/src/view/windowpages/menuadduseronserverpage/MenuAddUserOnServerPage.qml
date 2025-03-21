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

    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
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

    ListModel {
        id:modell
        ListElement {name: "asf"}
        ListElement {name: "asf"}
        ListElement {name: "asf"}
        ListElement {name: "asf"}
        ListElement {name: "asf"}
        ListElement {name: "asf"}
        ListElement {name: "asf"}
    }

    ListView {
        anchors.top: windowText.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
        spacing: 10
        model: modell
        interactive: true
        clip: true

        delegate: CandidateUserObject {
            width: parent ? parent.width : undefined
            height: 50
        }
    }

}
