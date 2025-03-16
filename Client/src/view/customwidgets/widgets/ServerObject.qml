import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    width: Sizes.maxServerObjectWidth // 55
    height: Sizes.maxServerObjectHeight // 55

    palette.buttonText: "black"
    font.pixelSize: Sizes.serverObjectTextSize // 32
    font.family: Fonts.textFont

    background: Rectangle {
        radius: Sizes.serverObjectRadius // 10
        color: "#93CCFF"
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
