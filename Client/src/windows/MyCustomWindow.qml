import QtQuick 2.15
import QtQuick.Controls 2.15
import "../resources/"

ApplicationWindow {
    id: mainWindow

    visible: true
    width: 640
    height: 480

    flags: Qt.Window | Qt.FramelessWindowHint // Отключение стандартного обрамления окна

    property int previousX // переменная хранящая X зажатого курсора
    property int previousY // переменная хранящая Y зажатого курсора

    readonly property real toolBarHeight: toolBar.height // переменная хранящая размер toolBar

    readonly property real maxWidthSize: Screen.desktopAvailableWidth // переменная хранящая максимальную ширина окна
    readonly property real maxHeightSize: Screen.desktopAvailableHeight // переменная хранящая максимальную длину окна

    property real lastWidthSize: 640 // переменная хранящая последнюю не максимальную ширина окна
    property real lastHeightSize: 480 // переменная хранящая последнюю не максимальную длину окна

    property real lastWindowX: mainWindow.x // переменная хранящая последее положение окна по X
    property real lastWindowY: mainWindow.y // переменная хранящая последнее положение окна по Y

    property int mouseAreaHeightSize: 2 // переменная хранящая размер для MouseArea

    onWidthChanged: {
        if(width != maxWidthSize)
        {
            lastWidthSize = width
        }
    }

    onHeightChanged: {
        if(height != maxHeightSize)
        {
            lastHeightSize = height
        }
    }

    Rectangle {
        id: toolBar
        width: parent.width
        height: 34
        color: Colors.toolBarColor

        Button {
            id: closeButton
            anchors.right: toolBar.right
            width: 34
            height: 34

            Image {
                source: "qrc:/resources/img/CloseApplication.svg"
                anchors.centerIn: parent
                width: 34
                height: 34
            }

            background: Rectangle {
                color: "white"
            }
        }

        MouseArea { // перемещение окна
            anchors.fill: parent

            onPressed: {
                mainWindow.previousX = mouseX
                mainWindow.previousY = mouseY
            }

            onDoubleClicked: {
                if(mainWindow.maxWidthSize == mainWindow.width && mainWindow.maxHeightSize == mainWindow.height) // сузить окно до прошлого состояния
                {
                    mainWindow.setWidth(mainWindow.lastWidthSize)
                    mainWindow.setHeight(mainWindow.lastHeightSize)
                    mainWindow.setX(mainWindow.lastWindowX)
                    mainWindow.setY(mainWindow.lastWindowY)
                }
                else // расятнуть окно на максимум
                {
                    mainWindow.lastWidthSize = mainWindow.width
                    mainWindow.lastHeightSize = mainWindow.height
                    mainWindow.setWidth(mainWindow.maxWidthSize)
                    mainWindow.setHeight(mainWindow.maxHeightSize)
                }
            }

            onPositionChanged: {
                mainWindow.setX(mainWindow.x + (mouseX - mainWindow.previousX))
                mainWindow.setY(mainWindow.y + (mouseY - mainWindow.previousY))
                mainWindow.lastWindowX = mainWindow.x
                mainWindow.lastWindowY = mainWindow.y
            }
        }
    }

    MouseArea { // изменение размера top
        height: mainWindow.mouseAreaHeightSize

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        acceptedButtons: Qt.LeftButton
        hoverEnabled: true

        cursorShape: Qt.SizeVerCursor

        onPressed: {
            mainWindow.startSystemResize(Qt.TopEdge)
        }
    }
}
