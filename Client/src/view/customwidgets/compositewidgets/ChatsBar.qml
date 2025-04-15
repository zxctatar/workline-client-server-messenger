pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"
import "../widgets"
import "../../windows"

Item {
    id: chatsBar

    width: Sizes.maxChatBarHeight // 230

    property var controller // chatsBarController

    property var currentIndex: -1

    Connections {
        target: chatsBar.controller

        function onServerChangedSignal() {
            chatsBar.currentIndex = -1
        }
    }

    Rectangle {
        anchors.fill: parent

        color: "#729EC6"

        ListView {
            anchors.fill: parent

            model: chatsBar.controller.getChatModel()
            clip: true
            interactive: true
            delegate: ChatObject {
                required property int id
                required property string name
                required property bool isChat
                required property int companionId
                required property string lastMess

                chatId: id
                displayName: name
                lastMessage: lastMess

                selected: chatsBar.currentIndex == id ? true : false

                width: parent ? parent.width : null
                height: Sizes.maxChatObjectHeight // 70

                onClicked: {
                    if(isChat == false)
                    {
                        createChatWindow.companionId = companionId
                        createChatWindow.open()
                    }
                    else if(chatsBar.currentIndex != id)
                    {
                        chatsBar.currentIndex = id
                        chatsBar.controller.sendChatId(id)
                    }
                }
            }
        }
    }

    CreateChatWindow {
        id: createChatWindow
        parent: Overlay.overlay
        anchors.centerIn: parent

        onCreateChat: function(companionId) {
            chatsBar.controller.createChat(companionId)
        }
    }
}
