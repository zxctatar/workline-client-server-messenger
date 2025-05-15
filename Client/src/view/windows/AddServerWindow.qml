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

    signal addServerSignal(string encodedFilePath, string serverName, string serverDescription)

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
        radius: Sizes.windowsRadius // 26
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 20
        font.pixelSize: Sizes.menuTextSize // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Создать сервер"
    }

    Separator {
        id: sep
        anchors.top: windowText.bottom
        anchors.topMargin: 20
        width: parent.width - 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ColumnLayout {
        id: layout
        anchors.top: sep.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        spacing: 15

        AddImage {
            id: addImage
            Layout.preferredWidth: Sizes.addImageWidth // 100
            Layout.preferredHeight: Sizes.addImageHeight // 100
            Layout.alignment: Qt.AlignHCenter
            radius: Sizes.addImageRadius // 50

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
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            font.pixelSize: Sizes.standartTextSize // 16
            placeholderText: "Название сервера"
        }

        InputField {
            id: inputFieldDescription
            Layout.fillWidth: true
            Layout.preferredHeight: 170
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            wrapMode: TextArea.Wrap
            font.pixelSize: Sizes.standartTextSize // 16
            placeholderText: "Описание"
        }

        ErrorText {
            id: errorText
            visible: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
        }

        MyButton {
            Layout.preferredWidth: 173
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter
            text: "Создать"

            onClicked: {
                if(inputFieldName.length == 0)
                {
                    errorText.text = "Введите имя сервера"
                    errorText.visible = true
                    return
                }

                errorText.visible = false

                addServerWindow.addServerSignal(addImage.encodedFilePath, inputFieldName.text, inputFieldDescription.text)
            }
        }
    }
}
