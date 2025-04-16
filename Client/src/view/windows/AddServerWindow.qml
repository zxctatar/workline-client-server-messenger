import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../resources"
import "../customwidgets/widgets"

Popup {
    id: addServerWindow
    width: Sizes.maxAddServerWindowWidth // 475
    height: Sizes.maxAddServerWindowHeight // 550
    modal: true
    closePolicy: addImage.isFileDialogOpen ? Popup.NoAutoClose : Popup.CloseOnEscape | Popup.CloseOnPressOutside

    signal addServerSignal(string base64Image, string serverName, string serverDescription)

    property var notificationManager // ServerTable notificationManager

    function serverNameExists() {
        errorText.visible = false
        addServerWindow.notificationManager.showNotificationManager("Имя занято!")
    }

    function errorCreateServer() {
        errorText.visible = false
        addServerWindow.notificationManager.showNotificationManager("Ошибка на сервере!")
    }

    function clearInputFields() {
        inputFieldName.clear()
        inputFieldDescription.clear()
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
        color: Colors.addServerWindowBackgroundColor
        radius: Sizes.radiusAddServerWindow // 5
    }

    ColumnLayout {
        id: layout
        anchors.centerIn: parent
        spacing: 18

        AddImage {
            id: addImage
            Layout.preferredWidth: 100
            Layout.preferredHeight: 100
            Layout.alignment: Qt.AlignHCenter

            onBadImage: {
                errorText.text = "Неверное изображение"
                errorText.visible = true
            }

            onDone: {
                errorText.visible = false
            }
        }

        InputField {
            id: inputFieldName
            Layout.preferredWidth: 375
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            font.pixelSize: Sizes.addServerWindowFontSize // 16
            placeholderText: "Название сервера"
        }

        InputField {
            id: inputFieldDescription
            Layout.preferredWidth: 375
            Layout.preferredHeight: 250
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            wrapMode: TextArea.Wrap
            font.pixelSize: Sizes.addServerWindowFontSize // 16
            placeholderText: "Описание"
        }

        ErrorText {
            id: errorText
            visible: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
        }

        Item {
            Layout.fillHeight: true
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

                addServerWindow.addServerSignal(addImage.base64Image, inputFieldName.text, inputFieldDescription.text)
            }
        }
    }
}
