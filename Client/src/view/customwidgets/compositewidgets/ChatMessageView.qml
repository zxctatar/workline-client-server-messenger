pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import "../widgets"

Item {
    id: chatMessageView

    property var controller // chatHistory chatHistoryController
    property var notificationManager
    property int selectedChat: -1
    property bool selectedIsGroup: false

    clip: true

    function getChatData() {
        chatMessageView.controller.getChatData(chatMessageView.selectedChat, chatMessageView.selectedIsGroup)
    }

    Connections {
        target: chatMessageView.controller

        function onScrollDownSignal() {
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

        header: Item {
            width: 1
            height: 10
        }

        delegate: ChatMessageObject {
            required property int messageId
            required property bool companion
            required property string messages
            required property string avatarPath
            required property bool showAvatar
            required property bool isViewed
            required property string time

            width: listView.width
            isCompanion: companion
            message: messages
            path: avatarPath
            visibleAvatar: showAvatar
            messageTime: time
            viewed: isViewed

            Component.onCompleted: {
                if (isCompanion && !viewed) {
                    chatMessageView.controller.markMessageAsRead(messageId)
                }
            }
        }

        ScrollBar.vertical: ScrollBar {
            id: verticalScroll
            policy: ScrollBar.AsNeeded
        }
    }
}
