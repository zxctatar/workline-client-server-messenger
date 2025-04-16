import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1

Button {
    id: addImage

    readonly property string base64Image: Qt.btoa(image.source)
    property bool isFileDialogOpen: false
    signal badImage()
    signal done()

    background: Rectangle {
        radius: 10
        border.color: "#4EABFD"
        border.width: 1
        color: "#DDEFFF"
    }

    Image {
        id: image
        anchors.fill: parent
        visible: fileDialog.file !== ""
        source: fileDialog.file

        onStatusChanged: {
            if(status === Image.Ready)
            {
                if(image.width > 100 || image.height > 100)
                {
                    image.source = ""
                    addImage.badImage()
                }
                else
                {
                    addImage.done()
                }
            }
        }
    }

    Text {
        anchors.fill: parent
        width: parent.width - 5
        height: parent.height - 5
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 11
        wrapMode: Text.WordWrap
        color: "black"
        text: "Добавить изображение 100x100 (png, ico, svg)"
        visible: fileDialog.file == ""
    }

    FileDialog {
        id: fileDialog
        nameFilters: ["Image files (*.png *.ico *.svg)"]

        onAccepted: {
            addImage.isFileDialogOpen = false
        }

        onRejected: {
            addImage.isFileDialogOpen = false
        }
    }

    onClicked: {
        addImage.isFileDialogOpen = true
        fileDialog.open()
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor

        onClicked: {
            parent.clicked()
        }
    }
}
