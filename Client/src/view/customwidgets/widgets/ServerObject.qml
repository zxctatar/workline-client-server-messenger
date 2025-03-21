import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: serverObject

    property bool selected: false

    width: Sizes.maxServerObjectWidth // 55
    height: Sizes.maxServerObjectHeight // 55

    signal deleteServerClicked(int serverId)

    property int serverId

    palette.buttonText: "black"
    font.pixelSize: Sizes.serverObjectTextSize // 32
    font.family: Fonts.textFont

    background: Rectangle {
        radius: Sizes.serverObjectRadius // 10
        color: "#93CCFF"
        border.color: serverObject.selected ? "#00FF62" : "transparent"
        border.width: serverObject.selected ? 6 : 0
    }

    Menu {
        id: contextMenu

        MenuItem {
            text: "Удалить"

            onClicked: {
                serverObject.deleteServerClicked(serverObject.serverId)
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: (mouse) => {
            if(mouse.button == Qt.LeftButton)
            {
                parent.clicked()
            }
            else if(mouse.button == Qt.RightButton)
            {
                contextMenu.open()
            }
        }
    }
}
