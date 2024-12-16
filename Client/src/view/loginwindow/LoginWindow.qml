import QtQuick 2.15
import "../../resources"
import "../widgets"

Rectangle {
    id: loginWindow
    anchors.fill: parent

    color: Colors.windowBackgroundColor

    Column {
        anchors.centerIn: parent
        z: 1
        spacing: 50
        InputField {
            id: inputField1
            placeholderText: "Логин"
        }

        InputField {
            id: inputField2
            placeholderText: "Пароль"
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            inputField1.focus = false
            inputField2.focus = false
        }
    }
}
