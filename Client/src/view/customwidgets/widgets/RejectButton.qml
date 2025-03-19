import QtQuick 2.15
import QtQuick.Controls 2.1
import "../../../resources"

Button {
    id: rejectButton
    width: Sizes.maxRejectButtonWidth // 35
    height: Sizes.maxRejectButtonHeight // 35

    Image {
        anchors.fill: parent
        source: "qrc:/resources/img/no.svg"
    }

    background: Rectangle {
        color: rejectButton.hovered ? Colors.hoverRejectButtonColor : Colors.normalRejectButtonColor
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

