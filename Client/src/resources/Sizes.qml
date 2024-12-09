pragma Singleton

import QtQuick 2.15

QtObject {
    //MyCustomWindow
    readonly property int toolBarMouseAreaSize: 2 // переменная хранящая размер для MouseArea
    readonly property int toolBarHeight: 34 // размер toolBar

    readonly property int maxWindowWidthSize: Screen.desktopAvailableWidth // переменная хранящая максимальную ширина окна
    readonly property int maxWindowHeightSize: Screen.desktopAvailableHeight // переменная хранящая максимальную длину окна
    readonly property int minWindowWidthSize: 640
    readonly property int minWindowHeightSize: 480

}
