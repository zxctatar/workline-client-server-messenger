import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: createGropChatPage

    property int serverId
    property var controller // CreateGroupChatController

    signal backButtonClicked()
    signal nextButtonClicked()

    signal deleteController()

    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
    }

    Component.onDestruction: {
        createGropChatPage.deleteController()
    }

    BackButton {
        id: backButton
        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 25
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 20
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            createGropChatPage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 20
        font.pixelSize: Sizes.menuTextSize // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Создать групповой чат"
    }

    Separator {
        id: sep
        anchors.top: windowText.bottom
        anchors.topMargin: 20
        width: parent.width - 50
        anchors.horizontalCenter: parent.horizontalCenter
    }


    ColumnLayout {
        id: coll
        spacing: 10
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: sep.bottom
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        anchors.topMargin: 20
        anchors.bottomMargin: 20

        AddImage {
            id: addImage
            Layout.alignment: Qt.AlignHCenter
            radius: Sizes.addImageRadius // 50
            Layout.preferredWidth: Sizes.addImageWidth // 100
            Layout.preferredHeight: Sizes.addImageHeight // 100
        }

        InputField {
            id: inputFieldName
            Layout.preferredWidth: Sizes.createGroupChatInputFieldWidth // 375
            Layout.preferredHeight: Sizes.createGroupChatInputFieldHeight // 40
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: Sizes.standartTextSize // 16
            placeholderText: "Название чата"
        }

        ErrorText {
            id: errorText
            visible: false
            Layout.preferredWidth: Sizes.createGroupChatPageErrorTextWidth // 375
            Layout.alignment: Qt.AlignHCenter
        }

        MyButton {
            id: nextButton
            Layout.preferredWidth: Sizes.maxNextButtonWidth // 100
            Layout.preferredHeight: Sizes.maxNextButtonHeight // 50
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: Sizes.standartTextSize // 16
            text: "Далее"

            onClicked: {
                if(inputFieldName.length == 0)
                {
                    errorText.text = "Введите название чата"
                    errorText.visible = true
                    return
                }

                errorText.visible = false
                createGropChatPage.controller.saveAvatarAndName(addImage.encodedFilePath, inputFieldName.text)
                createGropChatPage.nextButtonClicked()
            }
        }
    }
}
