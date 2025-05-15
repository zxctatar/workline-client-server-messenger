import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: menuCreateTaskPage

    signal deleteController()
    signal backButtonClicked()

    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
    }

    Component.onDestruction: {
        menuCreateTaskPage.deleteController()
    }

    BackButton {
        id: backButton
        anchors.leftMargin: Sizes.backButtonLeftMarginSizeMenu // 10
        anchors.topMargin: Sizes.backButtonTopMarginSizeMenu // 10
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            menuCreateTaskPage.backButtonClicked()
        }
    }

    WindowText {
        id: windowText
        anchors.topMargin: Sizes.textTopMargin // 10
        font.pixelSize: Sizes.menuTextSize // 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Добавить задачу"
    }

    ScrollView {
        id: scrollView
        width: parent.width
        height: parent.height
        anchors.top: windowText.bottom
        clip: true

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOff

        contentItem: Flickable {
            id: flickable
            boundsBehavior: Flickable.StopAtBounds
            contentWidth: parent.width
            contentHeight: coll.height
            interactive: true

            ColumnLayout {
                id: coll
                spacing: 10
                anchors.fill: parent

                InputField {
                    id: inputFieldTaskName
                    Layout.topMargin: 20
                    Layout.preferredWidth: 375
                    Layout.preferredHeight: 40
                    Layout.alignment: Qt.AlignHCenter
                    font.pixelSize: Sizes.standartTextSize // 16
                    placeholderText: "Название задачи"
                }

                InputField {
                    id: inputFieldDescription
                    Layout.preferredWidth: 375
                    Layout.preferredHeight: 250
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                    wrapMode: TextArea.Wrap
                    font.pixelSize: Sizes.standartTextSize // 16
                    placeholderText: "Описание задачи"
                }
            }

        }
    }
}
