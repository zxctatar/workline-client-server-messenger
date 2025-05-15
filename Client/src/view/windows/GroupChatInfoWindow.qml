import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../resources"
import "../customwidgets/widgets"

Popup {
    id: groupChatInfoWindow
    width: 230
    height: 550
    modal: true

    property string avatarPath
    property string groupName
    property int usersCount

    closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape

    background: Rectangle {
        color: "#F2F2F2"
        radius: Sizes.windowsRadius // 26
    }

    Overlay.modal: Rectangle {
        color: Qt.rgba(0, 0, 0, 0.50)
    }

    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 100 }
    }

    exit: Transition {
        NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 100 }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 20
        font.pixelSize: Sizes.menuTextSize // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Профиль"
    }

    Separator {
        id: sep
        anchors.top: windowText.bottom
        anchors.topMargin: 20
        width: parent.width - 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ColumnLayout {
        id: coll
        anchors.top: sep.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        Layout.alignment: Qt.AlignHCenter
        Layout.preferredWidth: parent.width
        spacing: 3

        ViewImage {
            id: avatar
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            radius: 50
            Layout.preferredWidth: 100
            Layout.preferredHeight: 100
            path: groupChatInfoWindow.avatarPath
        }

        MenuText {
            id: groupName
            Layout.topMargin: 25
            text: "Название чата"
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        }

        MenuPageLabel {
            Layout.preferredHeight: 20
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            text: groupChatInfoWindow.groupName
        }

        MenuText {
            id: numberOfUsers
            Layout.topMargin: 25
            text: "Число пользователей"
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        }

        MenuPageLabel {
            Layout.preferredHeight: 20
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillWidth: true
            text: groupChatInfoWindow.usersCount
        }
    }
}
