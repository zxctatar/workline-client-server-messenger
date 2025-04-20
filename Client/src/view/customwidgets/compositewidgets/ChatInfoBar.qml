import QtQuick 2.15
import QtQuick.Controls
import "../../../resources"
import "../widgets"
import "../../windows"

Button {
    id: chatInfoBar

    property var controller // chatInfoBarController
    property int selectedChatId: -1

    property string groupChatName: ""
    property string firstName: ""
    property string lastName: ""
    property string middleName: ""
    property string email: ""
    property string phoneNumber: ""
    property string birthDate: ""
    property string avatarPath: ""
    property bool isGroupChat: false

    visible: selectedChatId == -1 ? false : true

    Connections {
        target: chatInfoBar.controller

        function onSetChatIdSignal(id) {
            chatInfoBar.selectedChatId = id
        }

        function onSetChatDataSignal(firstName, lastName, middleName, email, phoneNumber, birthDate, isGroupChat) {
            chatInfoBar.isGroupChat = isGroupChat
            chatInfoBar.firstName = firstName
            chatInfoBar.lastName = lastName
            chatInfoBar.middleName = middleName
            chatInfoBar.email = email
            chatInfoBar.phoneNumber = phoneNumber
            chatInfoBar.birthDate = birthDate
        }

        function onSetChatAvatarSignal(avatarPath) {
            chatInfoBar.avatarPath = avatarPath
        }

        function onClearChatDataSignal() {
            chatInfoBar.avatarPath = ""
            chatInfoBar.firstName = ""
            chatInfoBar.lastName = ""
            chatInfoBar.middleName = ""
            chatInfoBar.email = ""
            chatInfoBar.phoneNumber = ""
            chatInfoBar.birthDate = ""
        }

        function onClearChatIdSignal() {
            chatInfoBar.selectedChatId = -1
        }
    }

    Component.onCompleted: {
        chatInfoBar.controller.getChatId()
    }

    background: Rectangle {
        color: Colors.chatInfoBarBackgroundColor
    }

    Row {
        anchors.fill: parent
        anchors.leftMargin: 10
        spacing: 10

        ViewImage {
            id: image
            anchors.verticalCenter: parent.verticalCenter
            width: 50
            height: 50
            radius: 24
            path: chatInfoBar.avatarPath
        }

        ChatNameText {
            text: chatInfoBar.isGroupChat ? chatInfoBar.groupChatName : chatInfoBar.lastName + ' ' + chatInfoBar.firstName
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    MouseArea {
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor

        onClicked: {
            if(chatInfoBar.isGroupChat == false)
            {
                chatInfoWindow.open()
            }
        }
    }

    ChatInfoWindow {
        id: chatInfoWindow
        parent: Overlay.overlay
        anchors.centerIn: parent

        firstName: chatInfoBar.firstName
        lastName: chatInfoBar.lastName
        middleName: chatInfoBar.middleName
        avatarPath: chatInfoBar.avatarPath
        email: chatInfoBar.email
        phoneNumber: chatInfoBar.phoneNumber
        birthDate: chatInfoBar.birthDate
    }
}
