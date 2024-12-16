import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import "../../resources"

TextField {
    id: inputField
    width: Sizes.maxInputFieldWidth
    height: Sizes.maxInputFieldHeight

    color: Colors.pressedInputFieldTextColor

    leftPadding: Sizes.leftPaddingSize // 25
    rightPadding: Sizes.rightPaddingSize // 25
    topPadding: Sizes.topPaddingSize // 15
    bottomPadding: Sizes.bottomPaddingSize // 15

    placeholderTextColor: Colors.normalInputFieldTextColor

    font.pixelSize: Sizes.inputFieldTextSize // 26
    font.family: Fonts.textFont

    background: Rectangle {
        radius: Sizes.radiusInputFieldRectangle // 10
        color: parent.activeFocus ? Colors.pressedInputFieldColor : Colors.normalInputFieldColor
        border.color: parent.activeFocus ? Colors.pressedInputFieldBorderColor : Colors.normalInputFieldBorderColor
        layer.enabled: true
        layer.effect: DropShadow {
            anchors.fill: parent
            transparentBorder: Shadows.transparentBorder // true
            radius: Shadows.radius // 5
            color: Shadows.shadowColor
        }
    }
}
