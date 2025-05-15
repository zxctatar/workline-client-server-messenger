import QtQuick 2.15
import "../../../resources"

Text {
    font.family: Fonts.textFont
    font.weight: Fonts.normalWeight
    font.pixelSize: Sizes.standartTextSize // 16
    color: Colors.chatLastMessageTextColor
    elide: Text.ElideRight
    clip: true
}
