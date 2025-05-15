import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: approveButton
    width: Sizes.maxApproveButtonWidth // 35
    height: Sizes.maxApproveButtonHeight // 35

    Image {
        anchors.fill: parent
        source: approveButton.hovered ? "qrc:/resources/img/YesHovered.svg" : "qrc:/resources/img/YesNormal.svg"
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
