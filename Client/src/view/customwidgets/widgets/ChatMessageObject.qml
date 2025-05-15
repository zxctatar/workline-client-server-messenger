import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Item {
    id: chatMessageObject
    property string message
    property bool isCompanion
    property string path
    property bool visibleAvatar
    property bool viewed
    property string messageTime

    property string processedMessage: {
        const maxLen = 30
        const words = message.split(" ")
        return words.map(w => w.length > maxLen ? w.split("").join("\u200B") : w).join(" ")
    }

    width: parent ? parent.width : 100
    height: backgroundRect.height

    Row {
        anchors.fill: parent
        anchors.left: parent.left
        spacing: 10
        anchors.leftMargin: chatMessageObject.visibleAvatar ? 10 : 65

        ViewImage {
            visible: chatMessageObject.visibleAvatar
            width: Sizes. chatMessageObjectImageWidth // 45
            height: Sizes. chatMessageObjectImageHeight // 45
            radius: Sizes.imageRadius // 24
            path: chatMessageObject.path
            anchors.bottom: backgroundRect.bottom
        }

        Rectangle {
            id: backgroundRect
            color: chatMessageObject.isCompanion ? Colors.chatMessageCandidateColor : Colors.chatMessageUserColor
            radius: Sizes.chatMessageObjectRadius // 12

            property int checkWidth: chatMessageObject.isCompanion ? 0 : 26

            width: Math.min(messageText.paintedWidth + messageTime.paintedWidth + 5 + 20 + checkWidth, Sizes.chatMessageObjectWidth) // 400
            height: messageText.paintedHeight + 20

            Text {
                id: messageText
                text: chatMessageObject.processedMessage
                wrapMode: Text.WordWrap
                width: Math.min(
                    Math.min(
                        Sizes.chatMessageObjectWidth - messageTime.implicitWidth - 20,
                        chatMessageObject.width - 40 - 50 - messageTime.paintedWidth - 10 - 15 - 50
                    ),
                    implicitWidth
                )

                x: 10
                y: 10

                font.family: Fonts.textFont
                font.weight: Fonts.normalWeight
                font.pixelSize: Sizes.standartTextSize // 16
                color: Colors.chatMessageTextColor
            }

            Text {
                id: messageTime
                text: chatMessageObject.messageTime
                width: paintedWidth
                anchors.right: chatMessageObject.isCompanion ? backgroundRect.right : check.left
                anchors.rightMargin: 10
                anchors.bottom: backgroundRect.bottom
                anchors.bottomMargin: 5

                font.family: Fonts.textFont
                font.weight: Fonts.normalWeight
                font.pixelSize: Sizes.smallTextSize // 12
                color: Colors.chatMessageTextColor
            }

            Image {
                id: check
                source: chatMessageObject.viewed ? "qrc:/resources/img/checkYesUser.svg" : "qrc:/resources/img/checkNoUser.svg"
                visible: chatMessageObject.isCompanion ? false : true
                width: 16
                height: 16
                anchors.right: backgroundRect.right
                anchors.rightMargin: 10
                anchors.bottom: backgroundRect.bottom
                anchors.bottomMargin: 5
            }
        }
    }
}
