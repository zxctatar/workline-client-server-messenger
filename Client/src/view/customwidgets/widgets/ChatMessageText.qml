import QtQuick 2.15
import "../../../resources"

Text {
    font.family: Fonts.windowTextFont
    font.pixelSize: Sizes.chatMessageTextSizes // 15
    color: Colors.chatMessageTextColor
    elide: Text.ElideRight
    clip: true
}
