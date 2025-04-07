import QtQuick 2.15
import "../../../resources"

Text {
    font.family: Fonts.windowTextFont
    font.pixelSize: Sizes.chatNameTextSize // 16
    color: Colors.chatNameTextColor
    elide: Text.ElideRight
    clip: true
}
