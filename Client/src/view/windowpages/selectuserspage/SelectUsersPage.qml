import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: selectUsersPage

    signal backButtonClicked()
    signal buttonDoneClicked()

    property var controller

    background: Rectangle {
        color: "#D3E3F1"
    }

    Component.onCompleted: {

    }

    Component.onDestruction: {

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

    ListModel {
        id: modell
        ListElement {name: "123"}
        ListElement {name: "123"}
        ListElement {name: "123"}
        ListElement {name: "123"}
        ListElement {name: "123"}
    }

    ListView {
        id: listView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: refreshbutton.top
        anchors.top: backButton.bottom
        clip: true
        spacing: 10
        model: modell

        delegate: AddUsersObject {
            displayName: "123"
            width: parent.width
            height: 40
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
            selectUsersPage.buttonDoneClicked()
        }
    }
}
