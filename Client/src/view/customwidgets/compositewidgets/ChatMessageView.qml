pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import "../widgets"

ScrollView {
    id: chatMessageView

    property var controller
    property var notificationManger

    clip: true

    contentItem: Flickable {
        id: flickable
        boundsBehavior: Flickable.StopAtBounds
        contentWidth: parent.width
        contentHeight: parent.height

        ListView {
            id: listView
            width: flickable.width
            height: flickable.height
            spacing: 10
            model: modell
            interactive: false
            clip: true

            delegate: ChatMessageObject {
                required property string name
                required property string messages

                width: listView.width
                isCandidate: name === "a"
                message: messages
            }
        }
    }

    ListModel {
        id: modell
        ListElement { name: "a"; messages: "Привет, я кандидат. Очень длинный текст, который должен автоматически переноситься на следующую строку." }
        ListElement { name: "b"; messages: "Я не кандидат, но всё равно тут." }
        ListElement { name: "b"; messages: "Вот обычное сообщение с пробелами, а вотэтооченьдлинноесловокотороеневлезетвстрокуипереносится" }
    }
}
