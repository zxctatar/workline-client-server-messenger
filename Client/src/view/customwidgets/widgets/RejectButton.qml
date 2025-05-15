import QtQuick 2.15
import QtQuick.Controls 2.1
import "../../../resources"

Button {
    id: rejectButton
    width: Sizes.maxRejectButtonWidth // 35
    height: Sizes.maxRejectButtonHeight // 35

    Image {
        anchors.fill: parent
        source: rejectButton.hovered ? "qrc:/resources/img/NoHovered.svg" : "qrc:/resources/img/NoNormal.svg"
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

