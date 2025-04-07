import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

MyButton {
    id: createChatButton
    width: Sizes.maxCreateChatButtonWidth // 75
    height: Sizes.maxCreateChatButtonHeight // 30

    property string displayText

    text: displayText
    font.pixelSize: Sizes.fontPixelSizeCreateChatButton // 14

    background: Rectangle {
        color: createChatButton.hovered ? Colors.hoverButtonColor : Colors.normalButtonColor
        radius: Sizes.createChatButtonRadius // 0
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
