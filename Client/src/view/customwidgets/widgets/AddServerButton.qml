import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: addServer

    width: Sizes.maxAddServerButtonWidth // 55
    height: Sizes.maxAddServerButtonHeight // 55

    background: Rectangle {
        color: Colors.addServerButtonBackgroundColor
        radius: Sizes.serverTableWidgetRadius // 28
    }

    Image {
        source: addServer.hovered ? "qrc:/resources/img/PlusHovered.svg" : "qrc:/resources/img/PlusNormal.svg"
        anchors.centerIn: parent
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
