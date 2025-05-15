import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: menuWidget
    width: Sizes.menuWidgetWidth // 200
    height: Sizes.menuWidgetHeight // 50
    palette.buttonText: Colors.menuWidgetTextColor
    font.pixelSize: Sizes.standartTextSize // 16
    font.family: Fonts.textFont
    font.weight: menuWidget.hovered ? Fonts.boldWeight : Fonts.normalWeight

    background: Rectangle {
        color: Colors.normalMenuWidgetColor
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
