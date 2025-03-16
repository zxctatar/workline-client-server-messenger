import QtQuick 2.15
import QtQuick.Controls
import "../../../resources"

Item {
    id: label
    property string text

    Label {
        id: inputField
        width: parent.width
        font.pixelSize: 16
        font.family: Fonts.textFont

        background: Rectangle {
            color: "transparent"
        }

        color: "black"

        text: label.text
    }
    Rectangle {
        anchors.top: inputField.bottom
        width: parent.width
        height: 2
        color: "#B0D5FF"
        radius: 2
    }
}
