import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: menuButton
    width: Sizes.menuButtonWidth // 47
    height: Sizes.menuButtonHeight // 47

    background: Rectangle {
        color: Colors.menuButtonBackgroundColor
    }

    Image {
        anchors.fill: parent
        source: menuButton.hovered ? "qrc:/resources/img/MenuButtonHovered.svg" : "qrc:/resources/img/MenuButtonNormal.svg"
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
