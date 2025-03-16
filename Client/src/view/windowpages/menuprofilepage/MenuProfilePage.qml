import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: menuProfilePage

    signal backButtonClicked()

    property string firstName
    property string lastName
    property string middleName
    property string email
    property string phoneNumber


    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
    }

    BackButton {
        id: backButton
        width: 40
        height: 40

        anchors.leftMargin: 7
        anchors.topMargin: 7
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            menuProfilePage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: 10
        font.pixelSize: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Профиль"
    }

    ColumnLayout {
        id: layout
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: backButton.bottom
        spacing: Sizes.mainPageWidgetsSpacing

        MenuText {
            id: firstname
            Layout.topMargin: 10
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
