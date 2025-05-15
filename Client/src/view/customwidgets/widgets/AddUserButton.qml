import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: addUserButton
    width: Sizes.addUserButtonWidth // 35
    height: Sizes.addUserButtonHeight // 35

    Image {
        anchors.fill: parent
        source: addUserButton.hovered ? "qrc:/resources/img/AddHovered.svg" : "qrc:/resources/img/AddNormal.svg"
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
