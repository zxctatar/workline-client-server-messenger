import QtQuick 2.15
import "../widgets"

Item {
    id: chatHistory

    property var controller
    property var notificationManager

    property var selectedChat: -1

    Connections {
        target: chatHistory.controller

        function onSetChatIdSignal(id) {
            chatHistory.selectedChat = id
        }
    }

    ChatMessageView {
        controller: chatHistory.controller
        notificationManager: chatHistory.notificationManager
        selectedChat: chatHistory.selectedChat

        anchors.bottom: chatInput.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
    }

    ChatMessageInput {
        id: chatInput
        controller: chatHistory.controller
        selectedChat: chatHistory.selectedChat

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
