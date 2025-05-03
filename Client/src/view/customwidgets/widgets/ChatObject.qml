pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import "../../../resources"

Button {
    id: chatObject

    property int chatId

    property bool selected: false

    property bool isGroup
    property string displayName
    property string lastMessage
    property string path
    property int messageCount

    property string processedLastMessage: {
        const words = lastMessage.split("\n")
        return words[0]
    }

    background: Rectangle {
        color: chatObject.selected ? Colors.selectedChatColor : (chatObject.hovered ? "#85B4DE" : Colors.normalChatColor)
    }

    Row {
        id: rowLayout
        anchors.fill: parent
        anchors.margins: Sizes.chatObjectMargins // 7
        spacing: Sizes.chatObjectWidgetSpacing // 10

        Rectangle {
            id: recta
            radius: 24
            width: Sizes.maxChatObjectImageWidth // 50
            height: Sizes.maxChatObjectImageHeight // 50
            anchors.verticalCenter: parent.verticalCenter
            color: "transparent"

            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    width: recta.width
                    height: recta.height
                    radius: recta.radius
                }
            }

            Image {
                id: avatar
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                source: chatObject.isGroup ? (chatObject.path == "" ? "qrc:/resources/img/groupAvatar.svg" : chatObject.path) : (chatObject.path == "" ? "qrc:/resources/img/avatar.svg" : chatObject.path)
            }
        }

        Column {
            spacing: Sizes.chatObjectTextSpacing // 8
            anchors.verticalCenter: parent.verticalCenter
            width: rowLayout.width - avatar.width - rowLayout.spacing - notif.width - 10

            ChatNameText {
                id: nameText
                text: chatObject.displayName
                width: parent.width
            }

            ChatMessageText {
                id: messageText
                text: chatObject.processedLastMessage
                width: parent.width
            }
        }

        Rectangle {
            id: notif
            anchors.verticalCenter: parent.verticalCenter
            radius: 30
            clip: true

            visible: chatObject.messageCount > 0 ? true : false
            color: "#969BFF"

            width: 30
            height: 30

            Text {
                text: chatObject.messageCount
                anchors.centerIn: parent
                font.family: Fonts.windowTextFont
                font.pixelSize: Sizes.chatNameTextSize // 16
                elide: Text.ElideRight
                color: Colors.chatNameTextColor
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor

        onClicked: {
            parent.clicked()
        }
    }
}
