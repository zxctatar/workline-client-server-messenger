import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: chatObject

    property bool selected: false

    background: Rectangle {
        color: chatObject.selected ? Colors.selectedChatColor : Colors.normalChatColor
    }

    Image {
        anchors.topMargin: 7
        anchors.leftMargin: 7
        anchors.bottomMargin: 7
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left

        width: 63
        height: 63
        source: "qrc:/resources/img/avatar.svg"
    }
}
