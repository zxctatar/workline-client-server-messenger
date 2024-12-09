import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import "../resources" //Colors //Sizes

ApplicationWindow {
    id: mainWindow

    visible: true
    width: 640
    height: 480

    maximumWidth: Sizes.maxWindowWidthSize
    maximumHeight: Sizes.maxWindowHeightSize
    minimumWidth: Sizes.minWindowWidthSize
    minimumHeight: Sizes.minWindowHeightSize

    flags: Qt.Window | Qt.FramelessWindowHint // Отключение стандартного обрамления окна

    property int previousX // переменная хранящая X зажатого курсора
    property int previousY // переменная хранящая Y зажатого курсора

    property int lastWidthSize: Sizes.minWindowWidthSize // переменная хранящая последнюю не максимальную ширина окна
    property int lastHeightSize: Sizes.minWindowHeightSize // переменная хранящая последнюю не максимальную длину окна

    property real lastWindowX: mainWindow.x // переменная хранящая последее положение окна по X
    property real lastWindowY: mainWindow.y // переменная хранящая последнее положение окна по Y

    function changeLastWindowX() // изменить последнюю позицию по x
    {
        lastWindowX = x
    }

    function changeLastWindowY() // изменить последнюю позицию по y
    {
        lastWindowY = y
    }

    function changeLastWidthSize() // изменить последнюю ширину
    {
        lastWidthSize = width
    }

    function changeLastHeightSize() // изменить последнюю длину
    {
        lastHeightSize = height
    }

    onWidthChanged: { // записываем последнюю позицию по x и не максимальную ширину при её изменении
        if(width != Sizes.maxWindowWidthSize)
        {
            changeLastWidthSize()
            changeLastWindowX()
        }
    }

    onHeightChanged: { // записываем последнюю позицию по y и не максимальную длину при её изменении
        if(height != Sizes.maxWindowHeightSize)
        {
            changeLastHeightSize()
            changeLastWindowY()
        }
    }

    Rectangle {
        id: toolBar
        width: parent.width
        height: Sizes.toolBarHeight
        color: Colors.toolBarColor
        z: 1

        layer.enabled: true
        layer.effect: DropShadow {
            anchors.fill: parent
            transparentBorder: true
            verticalOffset: 4
            radius: 4
            color: Colors.dropShadowToolBarColor
        }

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
                color: Colors.toolBarDefaultButtonColor
            }
        }

        MouseArea { // перемещение окна
            anchors.fill: parent

            onPressed: {
                mainWindow.previousX = mouseX
                mainWindow.previousY = mouseY
            }

            onDoubleClicked: {
                if(isMaximized())
                {
                    restoreWindow()
                }
                else
                {
                    maximizeWindow()
                }
            }

            onPositionChanged: {
                movingWindow()
            }

            function isMaximized() // проверка на максимальный размер приложения
            {
                return mainWindow.width === Sizes.maxWindowWidthSize && mainWindow.height === Sizes.maxWindowHeightSize;
            }

            function restoreWindow()  // сузить окно для прошлого состояния
            {
                mainWindow.setWidth(mainWindow.lastWidthSize);
                mainWindow.setHeight(mainWindow.lastHeightSize);
                mainWindow.setX(mainWindow.lastWindowX);
                mainWindow.setY(mainWindow.lastWindowY);
            }

            function maximizeWindow()  // растянуть окно на максимум
            {
                mainWindow.setWidth(Sizes.maxWindowWidthSize);
                mainWindow.setHeight(Sizes.maxWindowHeightSize);
            }

            function movingWindow() // установка окна в нужнрое положение по x, y и запоминаем их
            {
                mainWindow.setX(mainWindow.x + (mouseX - mainWindow.previousX))
                mainWindow.setY(mainWindow.y + (mouseY - mainWindow.previousY))
                mainWindow.changeLastWindowX()
                mainWindow.changeLastWindowY()
            }
        }
    }

    MouseArea { // изменение размера top
        height: Sizes.toolBarMouseAreaSize
        z: 2

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        acceptedButtons: Qt.LeftButton

        cursorShape: Qt.SizeVerCursor

        onPressed: {
            mainWindow.startSystemResize(Qt.TopEdge)
        }
    }

    MouseArea { // изменение окна bottom
        height: Sizes.toolBarMouseAreaSize

        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        acceptedButtons: Qt.LeftButton
        hoverEnabled: true

        cursorShape: Qt.SizeVerCursor

        onPressed: {
            mainWindow.startSystemResize(Qt.BottomEdge)
        }
    }

    MouseArea { // изменение окна left
        width: Sizes.toolBarMouseAreaSize

        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }

        acceptedButtons: Qt.LeftButton
        hoverEnabled: true

        cursorShape: Qt.SizeHorCursor

        onPressed: {
            mainWindow.startSystemResize(Qt.LeftEdge)
        }
    }

    MouseArea { // изменение окна right
        width: Sizes.toolBarMouseAreaSize

        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        acceptedButtons: Qt.LeftButton
        hoverEnabled: true

        cursorShape: Qt.SizeHorCursor

        onPressed: {
            mainWindow.startSystemResize(Qt.RightEdge)
        }
    }
}

