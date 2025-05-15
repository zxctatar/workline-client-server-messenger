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
        source: swither.isSelected == true ? (swither.hovered ? "qrc:/resources/img/NoHovered.svg" : "qrc:/resources/img/NoNormal") : (swither.hovered ? "qrc:/resources/img/YesHovered.svg" : "qrc:/resources/img/YesNormal")
    }

    background: Rectangle {
        color: "transparent"
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
