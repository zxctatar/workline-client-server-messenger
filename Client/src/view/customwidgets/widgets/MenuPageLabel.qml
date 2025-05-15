import QtQuick 2.15
import QtQuick.Controls
import "../../../resources"

Item {
    id: label
    property string text

    Label {
        id: inputField
        width: parent.width
        font.pixelSize: Sizes.standartTextSize // 16
        font.family: Fonts.textFont
        font.weight: Fonts.normalWeight

        background: Rectangle {
            color: "transparent"
        }

        color: "black"

        text: label.text
    }
    Rectangle {
        anchors.top: inputField.bottom
        width: parent.width
        height: 1
        color: "#6A707B"
        radius: 2
    }
}
