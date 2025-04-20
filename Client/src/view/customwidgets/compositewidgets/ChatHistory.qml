import QtQuick 2.15
import "../widgets"

Item {
    id: chatHistory

    property var controller // chatHistoryController
    property var notificationManager

    property var selectedChat: -1

    Connections {
        target: chatHistory.controller

        function onSetChatIdSignal(id) {
            chatHistory.selectedChat = id
        }

        function onClearChatIdSignal() {
            chatHistory.selectedChat = -1
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

        visible: chatHistory.selectedChat == -1 ? false : true
    }

    ChatMessageInput {
        id: chatInput
        controller: chatHistory.controller
        selectedChat: chatHistory.selectedChat

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        visible: chatHistory.selectedChat == -1 ? false : true
    }
}
