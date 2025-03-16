import QtQuick 2.15
import QtQuick.Controls
import "../../../resources"

Image {
    source: "qrc:/resources/img/hint-icon.svg"

    property alias toolTipText: textToolTip.text

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        // Отображение подсказки при наведении
        onEntered: toolTip.visible = true
        onExited: toolTip.visible = false
    }

    ToolTip {
        id: toolTip
        delay: 1000

        contentItem: Text {
            id: textToolTip
            font.family: Fonts.textFont
            font.pixelSize: Sizes.toolTipTextSize // 14
            color: Colors.toolTipTextColor
            text: ""
        }

        background: Rectangle {
            border.color: Colors.toolTipBorderColor
            color: Colors.toolTipBackgroundColor
            radius: Sizes.radiusToolTipSize // 5
        }
    }
}
