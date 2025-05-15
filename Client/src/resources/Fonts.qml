pragma Singleton
import QtQuick 2.15

Item {
    readonly property string textFont: textFont.name
    readonly property string boldWeight: Font.Bold
    readonly property string normalWeight: Font.Normal

    FontLoader {
        id: textFont
        source: "qrc:/resources/fonts/Onest-VariableFont_wght.ttf"
    }
}
