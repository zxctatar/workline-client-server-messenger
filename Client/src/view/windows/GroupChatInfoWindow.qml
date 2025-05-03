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
        color: "#D3E3F1"
        radius: 5
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

    ColumnLayout {
        id: coll
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        Layout.alignment: Qt.AlignHCenter
        Layout.preferredWidth: parent.width
        spacing: Sizes.mainPageWidgetsSpacing

        ViewImage {
            id: avatar
            Layout.topMargin: 10
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
