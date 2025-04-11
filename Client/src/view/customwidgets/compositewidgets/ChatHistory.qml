import QtQuick 2.15
import "../widgets"

Item {
    id: chatHistory

    property var controller

    property var selectedChat: -1

    ChatMessageInput {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
