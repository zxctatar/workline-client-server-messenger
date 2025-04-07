import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../resources"
import "../customwidgets/widgets"

Popup {
    id: createChatWindow
    width: 200
    height: 80
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
        radius: 5
    }

    MenuText {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Хотите создать чат?"
    }

    CreateChatButton {
        anchors.left: parent.left
        anchors.bottom: parent.bottom

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
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        displayText: "Нет"

        onClicked: {
            createChatWindow.companionId = -1
            createChatWindow.close()
        }
    }

}
