import QtQuick 2.15
import "../widgets"

Item {
    id: chatHistory

    property var controller

    property var selectedChat: -1

    ChatMessageView {
        anchors.bottom: chatInput.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
    }

    ChatMessageInput {
        id: chatInput
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
