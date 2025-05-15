import QtQuick 2.15
import "../../../resources"

Text {
    id: textButton

    signal clicked()

    property bool hovered: false

    font.family: Fonts.textFont
    font.weight: Fonts.normalWeight
    font.pixelSize: Sizes.standartTextSize // 16
    color: textButton.hovered ? Colors.textButtonHoveredTextColor : Colors.textButtonNormalTextColor

    MouseArea {
        id: mouseArea
        cursorShape: Qt.PointingHandCursor
        anchors.fill: parent
        hoverEnabled: true

        onEntered: textButton.hovered = true
        onExited: textButton.hovered = false

        onClicked: {
            parent.clicked()
        }
    }
}
