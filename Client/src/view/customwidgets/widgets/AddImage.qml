pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1
import Qt5Compat.GraphicalEffects
import "../../../resources"

Button {
    id: addImage

    readonly property string encodedFilePath: Qt.btoa(image.source)
    property bool isFileDialogOpen: false
    property int radius: 0
    property string path: ""
    property bool change: true
    signal badImage()
    signal done()

    background: Rectangle {
        radius: addImage.radius
        border.color: addImage.hovered ? Colors.addImageHoveredBorderColor : Colors.addImageNormalBorderColor
        border.width: 1
        color: addImage.hovered ? Colors.addImageHoveredBackgroundColor : Colors.addImageNormalBackgroundColor
    }

    Rectangle {
        id: recta
        radius: addImage.radius
        anchors.centerIn: parent
        anchors.margins: 1
        width: parent.width - 2
        height: parent.height - 2
        color: "transparent"

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                width: recta.width
                height: recta.height
                radius: recta.radius
            }
        }

        Image {
            id: image
            anchors.fill: parent
            visible: fileDialog.file !== ""
            source: addImage.path == "" ? fileDialog.file : addImage.path
            fillMode: Image.PreserveAspectCrop

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
    }

    Text {
        anchors.fill: parent
        width: parent.width - 5
        height: parent.height - 5
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: Sizes.smallTextSize // 12
        wrapMode: Text.WordWrap
        color: "black"
        text: "Добавить изображение 100x100 (png, ico, svg, jpeg, jpg)"
        visible: fileDialog.file == "" ?  (addImage.change ? true : false) : false
    }

    FileDialog {
        id: fileDialog
        nameFilters: ["Image files (*.png *.ico *.svg *.jpeg *.jpg)"]

        onAccepted: {
            addImage.isFileDialogOpen = false
        }

        onRejected: {
            addImage.isFileDialogOpen = false
        }
    }

    onClicked: {
        if(addImage.change)
        {
            addImage.isFileDialogOpen = true
            fileDialog.open()
        }
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
