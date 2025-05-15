import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../resources"
import "../customwidgets/widgets"

Popup {
    id: chatInfoWindow
    width: Sizes.maxChatInfoWindowWidth // 475
    height: Sizes.maxChatInfoWindowHeight // 550
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    property string firstName
    property string lastName
    property string middleName
    property string birthDate
    property string phoneNumber
    property string email
    property string avatarPath

    Overlay.modal: Rectangle {
        color: Qt.rgba(0, 0, 0, 0.50)
    }

    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 100 }
    }

    exit: Transition {
        NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 100 }
    }

    background: Rectangle {
        color: "#F2F2F2"
        radius: Sizes.windowsRadius // 26
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

    Item {
        id: fields
        anchors.top: sep.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 25
        anchors.rightMargin: 25

        ScrollView {
            anchors.fill: parent
            clip: true
            width: parent.width
            height: parent.height
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff

            contentItem: Flickable {
                id: flickable
                boundsBehavior: Flickable.StopAtBounds
                contentWidth: parent.width
                contentHeight: coll.height + 5
                interactive: true

                ColumnLayout {
                    id: coll
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: parent.width
                    spacing: 3

                    ViewImage {
                        id: avatar
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        radius: 50
                        Layout.preferredWidth: 100
                        Layout.preferredHeight: 100
                        path: chatInfoWindow.avatarPath
                    }

                    MenuText {
                        id: lastname
                        Layout.topMargin: 25
                        text: "Фамилия"
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    }

                    MenuPageLabel {
                        Layout.preferredHeight: 20
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        Layout.fillWidth: true
                        text: chatInfoWindow.lastName
                    }

                    MenuText {
                        id: firstname
                        Layout.topMargin: 25
                        text: "Имя"
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    }

                    MenuPageLabel {
                        Layout.preferredHeight: 20
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        Layout.fillWidth: true
                        text: chatInfoWindow.firstName
                    }

                    MenuText {
                        id: middlename
                        Layout.topMargin: 25
                        text: "Отчество"
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    }

                    MenuPageLabel {
                        Layout.preferredHeight: 20
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        Layout.fillWidth: true
                        text: chatInfoWindow.middleName
                    }

                    MenuText {
                        id: birthDate
                        Layout.topMargin: 25
                        text: "Дата рождения"
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    }

                    MenuPageLabel {
                        Layout.preferredHeight: 20
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        Layout.fillWidth: true
                        text: chatInfoWindow.birthDate
                    }

                    MenuText {
                        id: email
                        Layout.topMargin: 25
                        text: "Почта"
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    }

                    MenuPageLabel {
                        Layout.preferredHeight: 20
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        Layout.fillWidth: true
                        text: chatInfoWindow.email
                    }

                    MenuText {
                        id: phoneNumber
                        Layout.topMargin: 25
                        text: "Телефон"
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    }

                    MenuPageLabel {
                        Layout.preferredHeight: 20
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        Layout.fillWidth: true
                        text: chatInfoWindow.phoneNumber
                    }
                }
            }
        }
    }
}
