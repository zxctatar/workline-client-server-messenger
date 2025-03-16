import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: menuWidget
    width: Sizes.maxMenuWidgetWidth // 200
    height: Sizes.maxMenuWidgetHeight // 50
    palette.buttonText: Colors.normalButtonTextColor
    background: Rectangle {
        color: menuWidget.hovered ? Colors.hoveredMenuWidgetColor : Colors.normalMenuWidgetColor
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
