import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../resources"
import "../customwidgets/widgets"

Popup {
    id: createChatWindow
    width: 250
    height: 140
    modal: true

    property int companionId: -1

    signal createChat(int companionId)

    MouseArea {
        anchors.fill: parent
    }

    Overlay.modal: Rectangle {
        color: Qt.rgba(0, 0, 0, 0.50)
    }

    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 100 }
    }

    exit: Transition {
        NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 100 }
    }

    background: Rectangle {
        color: Colors.addServerWindowBackgroundColor
        radius: 26
    }

    MenuText {
        id: menuText
        anchors.top: parent.top
        anchors.topMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Хотите создать чат?"
    }

    Row {
        spacing: 5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: menuText.bottom
        anchors.topMargin: 10

        CreateChatButton {
            displayText: "Да"

            onClicked: {
                if(createChatWindow.companionId != -1)
                {
                    createChatWindow.createChat(createChatWindow.companionId)
                    createChatWindow.companionId = -1
                    createChatWindow.close()
                }
            }
        }

        CreateChatButton {
            displayText: "Нет"

            onClicked: {
                createChatWindow.companionId = -1
                createChatWindow.close()
            }
        }

    }
}
