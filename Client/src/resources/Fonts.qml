pragma Singleton
import QtQuick 2.15

QtObject {
    readonly property FontLoader windowTextFont: { // шрифт текста окна
        id: windowTextFont
        source: "qrc:/resources/fonts/Lato-SemiBold.ttf"
    }

    readonly property FontLoader textFont: { // шрифт текста (кнопок, полей и т.д.)
        id: textFont
        source: "qrc:/resources/fonts/Inter-Regular.otf"
    }
}
