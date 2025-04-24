import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: swither
    width: Sizes.maxSwitcherButtonWidth // 35
    height: Sizes.maxSwitcherButtonHeight // 35

    property bool isSelected: false

    Image {
        anchors.fill: parent
        source: swither.isSelected == true ? "qrc:/resources/img/no.svg" : "qrc:/resources/img/yes.svg"
    }

    background: Rectangle {
        color: swither.isSelected == true ? (swither.hovered ? Colors.switcherNoButtonHovered : Colors.switcherNoButtonNormal) : (swither.hovered ? Colors.switcherYesButtonHovered : Colors.switcherYesButtonNormal)
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
