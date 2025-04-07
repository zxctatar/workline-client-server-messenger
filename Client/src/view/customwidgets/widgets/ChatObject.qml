import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: chatObject

    property int chatId

    property bool selected: false

    property string displayName

    background: Rectangle {
        color: chatObject.selected ? Colors.selectedChatColor : (chatObject.hovered ? "#85B4DE" : Colors.normalChatColor)
    }

    Row {
        id: rowLayout
        anchors.fill: parent
        anchors.margins: Sizes.chatObjectMargins // 7
        spacing: Sizes.chatObjectWidgetSpacing // 10

        Image {
            id: avatar
            width: Sizes.maxChatObjectImageWidth // 50
            height: Sizes.maxChatObjectImageHeight // 50
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/resources/img/avatar.svg"
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
                text: "555777777"
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
