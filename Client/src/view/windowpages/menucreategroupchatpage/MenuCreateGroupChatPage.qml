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
        width: Sizes.maxBackButtonMenuWidth // 40
        height: Sizes.maxBackButtonMenuHeight // 40

        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 7
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 7
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            createGropChatPage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 10
        font.pixelSize: Sizes.menuTextSizeInMenu // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Создать групповой чат"
    }

    ColumnLayout {
        id: coll
        spacing: 10
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: windowText.bottom

        AddImage {
            id: addImage
            Layout.topMargin: 10
            Layout.alignment: Qt.AlignHCenter
            radius: 50
            Layout.preferredWidth: 100
            Layout.preferredHeight: 100
        }

        InputField {
            id: inputFieldName
            Layout.preferredWidth: 375
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: Sizes.addServerWindowFontSize // 16
            placeholderText: "Название чата"
        }

        ErrorText {
            id: errorText
            visible: false
            Layout.preferredWidth: 375
            Layout.alignment: Qt.AlignHCenter
        }
    }

    MyButton {
        id: refreshbutton
        width: Sizes.maxMenuApplicaionPageRefreshButtonWidth // 100
        height: Sizes.maxMenuApplicaionPageRefreshButtonHeight // 50
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Sizes.menuTextSizeInWidgets // 16
        anchors.bottom: parent.bottom
        text: "Далее"

        onClicked: {
            if(inputFieldName.length == 0)
            {
                errorText.text = "Введите название чата"
                errorText.visible = true
                return
            }

            errorText.visible = false
            createGropChatPage.controller.saveAvatarAndName(addImage.base64Image, inputFieldName.text)
            createGropChatPage.nextButtonClicked()
        }
    }
}
