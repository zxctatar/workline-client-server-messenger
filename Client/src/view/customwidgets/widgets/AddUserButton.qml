import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: addUserButton
    width: Sizes.maxAddUserButtonWidth // 35
    height: Sizes.maxAddUserButtonHeight // 35

    Image {
        anchors.centerIn: parent
        width: 19
        height: 19
        source: "qrc:/resources/img/add.svg"
    }

    background: Rectangle {
        color: "#9FCCF2"
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
