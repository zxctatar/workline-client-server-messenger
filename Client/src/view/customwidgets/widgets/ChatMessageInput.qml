pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import "../../../resources"

Item {
    id: chatInput
    width: parent.width
    height: Math.min(200, Math.max(52, chatMessageInput.implicitHeight + 20))

    property var controller // chatHistory chatHistoryController
    property int selectedChat: -1
    property bool selectedIsGroup: false

    Rectangle {
        id: chatInputBackground
        anchors.fill: parent
        color: "#383C45"

        radius: 0 // Убираем общий радиус
        clip: true // Обрезка содержимого по маске

        // Используем маску, чтобы закруглить только верхние углы
        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Item {
                width: chatInputBackground.width
                height: chatInputBackground.height

                Rectangle {
                    anchors.fill: parent
                    color: "white"
                    radius: 25
                    antialiasing: true
                    anchors.bottomMargin: -25 // тянем вниз, чтобы только верх был закруглён
                }
            }
        }

        Rectangle {
            radius: 25
            color: "#576172"
            anchors.fill: parent
            anchors.margins: 10

            ScrollView {
                id: chatScrollView
                anchors.fill: parent
                clip: true
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: ScrollBar.AlwaysOff

                contentItem: Flickable {
                    id: flickable
                    boundsBehavior: Flickable.StopAtBounds  // Отключает перескок
                    anchors.centerIn: parent
                    contentWidth: width
                    contentHeight: chatMessageInput.implicitHeight

                    TextArea {
                        id: chatMessageInput
                        width: parent.width
                        height: parent.height
                        anchors.centerIn: parent
                        wrapMode: TextArea.Wrap
                        placeholderText: "Напишите сообщение..."

                        leftPadding: Sizes.chatMessageLeftPadding // 30
                        rightPadding: Sizes.chatMessageRightPadding // 30

                        topPadding: Sizes.chatMessageTopPadding // 5
                        bottomPadding: Sizes.chatMessageBottomPadding // 5

                        verticalAlignment: TextInput.AlignVCenter
                        horizontalAlignment: TextInput.AlignLeft

                        font.family: Fonts.textFont
                        font.weight: Fonts.normalWeight
                        font.pixelSize: Sizes.standartTextSize // 16
                        color: Colors.chatMessageTextColor

                        onTextChanged: {
                            flickable.contentY = flickable.contentHeight - flickable.height
                        }

                        Keys.onPressed: function(event) {
                            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                                event.accepted = true
                                const trimmedText = chatMessageInput.text.trim()

                                if (event.modifiers & Qt.ShiftModifier) {
                                    if (trimmedText.length > 0) {
                                        chatMessageInput.insert(chatMessageInput.cursorPosition, '\n');
                                    }
                                } else if (trimmedText.length > 0) {
                                    chatInput.controller.sendMessage(chatInput.selectedChat, chatInput.selectedIsGroup, chatMessageInput.text)
                                    chatMessageInput.text = ""
                                }
                            }
                        }
                    }

                }

                Component.onCompleted: {
                    chatScrollView.ScrollBar.vertical.position = 0
                }

            }
        }
    }
}


