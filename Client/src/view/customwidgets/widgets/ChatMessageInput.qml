import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

ScrollView {
    id: chatScrollView
    width: parent.width
    height: Math.min(200, Math.max(56, chatMessageInput.implicitHeight))

    property var controller // chatHistory chatHistoryController
    property int selectedChat: -1

    clip: true
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff

    contentItem: Flickable {
        id: flickable
        boundsBehavior: Flickable.StopAtBounds  // Отключает перескок
    }

    Component.onCompleted: {
        chatScrollView.ScrollBar.vertical.position = 0
    }

    TextArea {
        id: chatMessageInput
        wrapMode: TextArea.Wrap
        placeholderText: "Напишите сообщение..."

        background: Rectangle {
            color: "#ADD8FC"
        }

        leftPadding: 30
        rightPadding: 30

        topPadding: 5
        bottomPadding: 5

        verticalAlignment: TextInput.AlignVCenter
        horizontalAlignment: TextInput.AlignLeft

        font.family: Fonts.windowTextFont
        font.pixelSize: Sizes.chatMessageTextSizes
        color: Colors.chatMessageTextColor

        Keys.onPressed: function(event) {
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter)
            {
                event.accepted = true
                const trimmedText = chatMessageInput.text.trim()

                if (event.modifiers & Qt.ShiftModifier)
                {
                    if (trimmedText.length > 0)
                    {
                        chatMessageInput.insert(chatMessageInput.cursorPosition, '\n');
                    }
                }
                else if (trimmedText.length > 0)
                {
                    chatScrollView.controller.sendMessage(chatScrollView.selectedChat, chatMessageInput.text)
                    chatMessageInput.text = ""
                }
            }
        }
    }
}
