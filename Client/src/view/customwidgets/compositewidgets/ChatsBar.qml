pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"
import "../widgets"
import "../../windows"

Item {
    id: chatsBar

    width: Sizes.chatBarHeight // 230

    property var controller // chatsBarController

    property int currentIndex: -1
    property bool currentIsGroup

    Connections {
        target: chatsBar.controller

        function onServerChangedSignal() {
            chatsBar.currentIndex = -1
        }
    }

    Rectangle {
        anchors.fill: parent

        color: Colors.chatsBarBackgroundColor

        ListView {
            anchors.fill: parent
            anchors.leftMargin: 7
            anchors.rightMargin: 7
            spacing: 5

            model: chatsBar.controller.getChatModel()
            clip: true
            interactive: true
            delegate: ChatObject {
                required property int id
                required property string name
                required property bool isChat
                required property int companionId
                required property string lastMess
                required property string imagePath
                required property bool isGroupChat
                required property int newMessageCount

                chatId: id
                displayName: name
                lastMessage: lastMess
                path: imagePath
                isGroup: isGroupChat
                messageCount: newMessageCount

                selected: chatsBar.currentIndex == id && chatsBar.currentIsGroup == isGroupChat? true : false

                width: parent ? parent.width : null
                height: Sizes.chatObjectHeight // 70

                onClicked: {
                    if(isChat == false && isGroupChat == false)
                    {
                        createChatWindow.companionId = companionId
                        createChatWindow.open()
                    }
                    else if(!selected)
                    {
                        chatsBar.currentIsGroup = isGroupChat
                        chatsBar.currentIndex = id
                        chatsBar.controller.clearChatData()
                        chatsBar.controller.setChatAvatar(imagePath)
                        chatsBar.controller.sendNewChatData(id, isGroupChat)
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
