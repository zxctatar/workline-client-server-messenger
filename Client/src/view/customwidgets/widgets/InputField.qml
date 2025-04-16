import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import "../../../resources"

TextField {
    id: inputField
    width: Sizes.maxInputFieldWidth // 410
    height: Sizes.maxInputFieldHeight // 48

    property bool isPassword: false

    leftPadding: Sizes.leftPaddingSize // 20
    rightPadding: showPasswordBtn.visible ? Sizes.rightPaddingSize + showPasswordBtn.width : Sizes.rightPaddingSize // 20
    topPadding: Sizes.topPaddingSize // 10
    bottomPadding: Sizes.bottomPaddingSize // 10

    color: Colors.pressedInputFieldTextColor
    placeholderTextColor: Colors.normalInputFieldTextColor

    font.pixelSize: Sizes.inputFieldTextSize // 16
    font.family: Fonts.textFont

    echoMode: showPasswordBtn.visible ? (showPasswordBtn.showPassword ? TextInput.Normal : TextInput.Password) : TextInput.Normal

    ShowPasswordButton {
        id: showPasswordBtn
        visible: inputField.isPassword
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: Sizes.showPasswordButtonRightMarginSize // 9
    }

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
