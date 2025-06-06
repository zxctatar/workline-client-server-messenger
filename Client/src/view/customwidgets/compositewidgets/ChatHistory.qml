import QtQuick 2.15
import "../widgets"

Item {
    id: chatHistory

    property var controller // chatHistoryController
    property var notificationManager

    property int selectedChat: -1
    property bool selectedIsGroup: false

    Connections {
        target: chatHistory.controller

        function onSetChatIdAndGroupSignal(id, isGroup) {
            chatHistory.selectedIsGroup = isGroup
            chatHistory.selectedChat = id

            chatMessageView.getChatData()
        }

        function onClearChatIdSignal() {
            chatHistory.selectedChat = -1
        }
    }

    ChatMessageView {
        id: chatMessageView
        controller: chatHistory.controller
        notificationManager: chatHistory.notificationManager
        selectedChat: chatHistory.selectedChat
        selectedIsGroup: chatHistory.selectedIsGroup

        anchors.bottomMargin: 2
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
        selectedIsGroup: chatHistory.selectedIsGroup

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        visible: chatHistory.selectedChat == -1 ? false : true
    }
}
