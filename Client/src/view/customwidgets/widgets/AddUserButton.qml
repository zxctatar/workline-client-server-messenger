import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: addUserButton
    width: Sizes.maxAddUserButtonWidth // 35
    height: Sizes.maxAddUserButtonHeight // 35

    Image {
        anchors.centerIn: parent
        width: Sizes.maxAddUserButtonImageWidth // 19
        height: Sizes.maxAddUserButtonImageHeight // 19
        source: "qrc:/resources/img/add.svg"
    }

    background: Rectangle {
        color: addUserButton.hovered ? Colors.hoveredAddUserButtonColor : Colors.normalAddUserButtonColor
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
