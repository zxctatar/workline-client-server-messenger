import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: menuProfilePage

    signal backButtonClicked()

    property var controller // profilePageController MenuWindow.qml

    property string avatarPath
    property string birthDate
    property string firstName
    property string lastName
    property string middleName
    property string email
    property string phoneNumber

    Component.onCompleted: {
        menuProfilePage.controller.getUserData()
    }

    Connections {
        target: menuProfilePage.controller

        function onSetUserDataSignal(avatarPath, birthDate, firstname, lastname, middlename, email, phoneNumber) {
            menuProfilePage.avatarPath = avatarPath
            menuProfilePage.birthDate = birthDate
            menuProfilePage.firstName = firstname
            menuProfilePage.lastName = lastname
            menuProfilePage.middleName = middlename
            menuProfilePage.email = email
            menuProfilePage.phoneNumber = phoneNumber
        }
    }

    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
    }

    BackButton {
        id: backButton
        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 25
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 20
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            menuProfilePage.backButtonClicked()
        }
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
        anchors.topMargin: 20
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

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
                    spacing: Sizes.menuProfilePageSpacing // 3

                    AddImage {
                        id: avatar
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        radius: Sizes.addImageRadius // 50
                        Layout.preferredWidth: Sizes.addImageWidth // 100
                        Layout.preferredHeight: Sizes.addImageHeight // 100
                        change: false
                        path: menuProfilePage.avatarPath
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
                        text: menuProfilePage.lastName
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
                        text: menuProfilePage.firstName
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
                        text: menuProfilePage.middleName
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
                        text: menuProfilePage.birthDate
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
                        text: menuProfilePage.email
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
                        text: menuProfilePage.phoneNumber
                    }
                }
            }
        }
    }
}
