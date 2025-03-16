import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: menuButton
    width: Sizes.maxMenuButtonWidth // 47
    height: Sizes.maxMenuButtonHeight // 47

    background: Rectangle {
        color: Colors.menuButtonBackgroundColor
    }

    Image {
        anchors.fill: parent
        source: "qrc:/resources/img/MenuButton.svg"
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
