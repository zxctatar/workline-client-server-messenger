pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import "../widgets"

Item {
    id: chatMessageView

    property var controller // chatHistory chatHistoryController
    property var notificationManager
    property int selectedChat: -1

    clip: true

    onSelectedChatChanged: {
        chatMessageView.controller.getChatHistory(chatMessageView.selectedChat)
    }

    Connections {
        target: chatMessageView.controller

        function onScrollDown() {
            listView.positionViewAtEnd()
        }
    }

    ListView {
        id: listView
        width: parent.width
        height: parent.height
        spacing: 10
        model: chatMessageView.controller.getModel()
        interactive: true
        clip: true

        boundsBehavior: Flickable.StopAtBounds

        delegate: ChatMessageObject {
            required property bool companion
            required property string messages

            width: listView.width
            isCompanion: companion
            message: messages
        }

        ScrollBar.vertical: ScrollBar {
            id: verticalScroll
            policy: ScrollBar.AsNeeded
        }
    }
}
