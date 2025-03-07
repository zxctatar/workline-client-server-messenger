import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../"

Popup {
    id: addServerWindow
    width: 475
    height: 550
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    signal addServerSignal(string serverName, string serverDescription)

    property var notificationManager // ServerTable notificationManager

    function serverNameExists() {
        errorText.visible = false
        addServerWindow.notificationManager.shownotificationManager("Имя занято!!!")
    }

    function errorCreateServer() {
        errorText.visible = false
        addServerWindow.notificationManager.shownotificationManager("Ошибка на сервере!!!")
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            inputFieldName.focus = false
            inputFieldDescription.focus = false
        }
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
        color: "#D3E3F1"
        radius: 5
    }

    ColumnLayout {
        id: layout
        anchors.centerIn: parent
        spacing: 18

        InputField {
            id: inputFieldName
            Layout.preferredWidth: 375
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            font.pixelSize: 18
            placeholderText: "Название сервера"
        }

        InputField {
            id: inputFieldDescription
            Layout.preferredWidth: 375
            Layout.preferredHeight: 300
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            wrapMode: TextArea.Wrap
            font.pixelSize: 18
            placeholderText: "Описание"
        }

        ErrorText {
            id: errorText
            visible: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
        }

        Item {
            Layout.fillHeight: true // Занимает всё оставшееся пространство
        }

        MyButton {
            Layout.preferredWidth: 375
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Создать"

            onClicked: {
                if(inputFieldName.length == 0)
                {
                    errorText.text = "Введите имя сервера"
                    errorText.visible = true
                    return
                }

                errorText.visible = false
                addServerWindow.addServerSignal(inputFieldName.text, inputFieldDescription.text)
            }
        }
    }

}
