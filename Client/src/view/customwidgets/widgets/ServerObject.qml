pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import "../../../resources"

Button {
    id: serverObject

    property bool isAdmin: false
    property bool selected: false

    width: Sizes.maxServerObjectWidth // 56
    height: Sizes.maxServerObjectHeight // 56

    signal deleteServerClicked(int serverId)

    property int serverId
    property string imagePath

    palette.buttonText: "black"
    font.pixelSize: Sizes.bigTextSize // 32
    font.family: Fonts.textFont
    font.weight: Fonts.normalWeight

    background: Rectangle {
        radius: Sizes.serverTableWidgetRadius // 28
        color: "#F2F2F2"
    }

    Rectangle {
        id: recta
        radius: Sizes.serverTableWidgetRadius // 28
        anchors.fill: parent
        anchors.verticalCenter: parent.verticalCenter
        color: "transparent"

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                width: recta.width
                height: recta.height
                radius: recta.radius
            }
        }

        Image {
            id: image
            anchors.fill: parent
            source: serverObject.imagePath
            visible: serverObject.imagePath !== ""
            z: 0
        }

        // Рамка поверх изображения
        Rectangle {
            anchors.fill: parent
            radius: Sizes.serverTableWidgetRadius // 28
            color: "transparent"
            border.color: serverObject.selected ? "#1AED77" : "transparent"
            border.width: serverObject.selected ? 6 : 0
            z: 1
        }
    }

    Menu {
        id: contextMenu

        MenuItem {
            text: "Удалить"
            onClicked: serverObject.deleteServerClicked(serverObject.serverId)
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: (mouse) => {
            if (mouse.button == Qt.LeftButton && !serverObject.selected) {
                parent.clicked()
            } else if (mouse.button == Qt.RightButton && serverObject.isAdmin) {
                contextMenu.open()
            }
        }
    }
}
