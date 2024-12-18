import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../resources"

Button {
    id: myButton
    width: Sizes.maxButtonWidth // 541
    height: Sizes.maxButtonHeight // 64

    palette.buttonText: myButton.hovered ? Colors.hoverButtonTextColor : Colors.normalButtonTextColor
    font.family: Fonts.textFont
    font.pixelSize: Sizes.buttonTextSize // 26

    background: Rectangle {
        color: myButton.hovered ? Colors.hoverButtonColor : Colors.normalButtonColor
        radius: Sizes.radiusButtonRectangle // 10
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
