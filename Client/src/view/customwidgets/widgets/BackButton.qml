import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: root
    width: Sizes.maxBackButtonRegPageWidth // 19
    height: Sizes.maxBackButtonRegPageHeight // 29

    Image {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        source: parent.hovered ? "qrc:/resources/img/back-arrow-hovered.svg" : "qrc:/resources/img/back-arrow-normal.svg"
    }

    background: Rectangle {
        color: Colors.backgroundBackButtonColor
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
