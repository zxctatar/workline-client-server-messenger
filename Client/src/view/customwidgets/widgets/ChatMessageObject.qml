import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Item {
    id: chatMessageObject
    property string message
    property bool isCompanion

    property string processedMessage: {
        const maxLen = 30
        const words = message.split(" ")
        return words.map(w => w.length > maxLen ? w.split("").join("\u200B") : w).join(" ")
    }

    width: parent ? parent.width : 100
    height: backgroundRect.height

    Rectangle {
        id: backgroundRect
        color: chatMessageObject.isCompanion ? Colors.chatMessageCandidateColor : Colors.chatMessageUserColor
        radius: 5
        anchors.left: parent.left
        anchors.leftMargin: 10

        width: Math.min(messageText.paintedWidth + 20, Sizes.maxChatMessageObjectWidth) //400
        height: messageText.paintedHeight + 20

        Text {
            id: messageText
            text: chatMessageObject.processedMessage
            wrapMode: Text.WordWrap
            width: Math.min(chatMessageObject.width - 40, Sizes.maxChatMessageObjectWidth - 20) // 380

            x: 10
            y: 10

            font.family: Fonts.windowTextFont
            font.pixelSize: Sizes.chatMessageTextSizes
            color: Colors.chatMessageTextColor
        }
    }
}
