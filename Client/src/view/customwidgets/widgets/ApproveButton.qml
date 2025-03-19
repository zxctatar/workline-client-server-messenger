import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: approveButton
    width: Sizes.maxApproveButtonWidth // 35
    height: Sizes.maxApproveButtonHeight // 35

    Image {
        anchors.fill: parent
        source: "qrc:/resources/img/yes.svg"
    }

    background: Rectangle {
        color: approveButton.hovered ? Colors.hoverApproveButtonColor : Colors.normalApproveButtonColor
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
