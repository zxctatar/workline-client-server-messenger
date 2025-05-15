import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

MyButton {
    id: createChatButton
    width: Sizes.createChatButtonWidth // 90
    height: Sizes.createChatButtonHeight // 40

    property string displayText

    text: displayText
    font.pixelSize: Sizes.standartTextSize // 16

    background: Rectangle {
        color: createChatButton.hovered ? Colors.hoverButtonColor : Colors.normalButtonColor
        radius: Sizes.createChatButtonRadius // 20
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
