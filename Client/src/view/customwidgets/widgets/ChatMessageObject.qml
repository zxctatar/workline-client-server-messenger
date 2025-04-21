import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Item {
    id: chatMessageObject
    property string message
    property bool isCompanion
    property string path
    property bool visibleAvatar

    property string processedMessage: {
        const maxLen = 30
        const words = message.split(" ")
        return words.map(w => w.length > maxLen ? w.split("").join("\u200B") : w).join(" ")
    }

    width: parent ? parent.width : 100
    height: backgroundRect.height

    Row {
        anchors.left: parent.left
        spacing: 10
        anchors.leftMargin: chatMessageObject.visibleAvatar ? 10 : 70

        ViewImage {
            visible: chatMessageObject.visibleAvatar
            width: 50
            height: 50
            radius: 24
            path: chatMessageObject.path
            anchors.bottom: backgroundRect.bottom
        }

        Rectangle {
            id: backgroundRect
            color: chatMessageObject.isCompanion ? Colors.chatMessageCandidateColor : Colors.chatMessageUserColor
            radius: Sizes.chatMessageObjectRadius // 5

            width: Math.min(messageText.paintedWidth + 20, Sizes.maxChatMessageObjectWidth) // 400
            height: messageText.paintedHeight + 20

            Text {
                id: messageText
                text: chatMessageObject.processedMessage
                wrapMode: Text.WordWrap
                width: Math.min(chatMessageObject.width - 40, Sizes.maxChatMessageObjectWidth - 20) // 380

                x: 10
                y: 10

                font.family: Fonts.windowTextFont
                font.pixelSize: Sizes.chatMessageTextSizes // 16
                color: Colors.chatMessageTextColor
            }
        }
    }

}
