import QtQuick 2.15
import QtQuick.Controls
import "../../../resources"

Item {
    TextField {
        id: inputField
        width: parent.width
        palette.text: "black"
        font.pixelSize: 16
        font.family: Fonts.textFont

        background: Rectangle {
            color: "transparent"
        }
    }
    Rectangle {
        anchors.top: inputField.bottom
        width: parent.width
        height: 2
        color: "#B0D5FF"
        radius: 2
    }
}
