pragma Singleton
import QtQuick 2.15

Item {
    readonly property alias textFont: textFont.name
    readonly property alias windowTextFont: windowTextFont.name

    FontLoader { // шрифт текста окна
        id: windowTextFont
        source: "qrc:/resources/fonts/Lato-SemiBold.ttf"
    }

    FontLoader { // шрифт текста (кнопок, полей и т.д.)
        id: textFont
        source: "qrc:/resources/fonts/Inter-Regular.otf"
    }
}
