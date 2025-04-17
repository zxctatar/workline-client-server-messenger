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

    property string displayName
    property string lastMessage
    property string path

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
                source: chatObject.path == "" ? "qrc:/resources/img/avatar.svg" : chatObject.path
            }
        }

        Column {
            spacing: Sizes.chatObjectTextSpacing // 8
            anchors.verticalCenter: parent.verticalCenter
            width: rowLayout.width - avatar.width - rowLayout.spacing

            ChatNameText {
                id: nameText
                text: chatObject.displayName
                width: parent.width
            }

            ChatMessageText {
                id: messageText
                text: chatObject.lastMessage
                width: parent.width
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
