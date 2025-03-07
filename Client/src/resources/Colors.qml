pragma Singleton
import QtQuick 2.15

QtObject {
    //window
    readonly property color windowBackgroundColor: "#DDEFFF" // цвет заднего фона окна

    readonly property color windowTextColor: "#373737" // цвет текста в окне

    //buttons
    readonly property color hoverButtonColor: "#1E88E5" // цвет кнопки когда навелись
    readonly property color normalButtonColor: "#4EABFD" // обычный цвет кнопки

    readonly property color hoverButtonTextColor: "#292929" // цвет текста кнопки когда навелись
    readonly property color normalButtonTextColor: "#373737" // цвет обычной кнопки

    //add server button
    readonly property color addServerButtonBackgroundColor: "#5EA9EA"

    //show password button
    readonly property color showPasswordButtonColor: "transparent" // цвет заднего фона кнопки показа пароля

    //error text
    readonly property color errorTextColor: "#FF0000" // цвет текста ошибки

    //popup
    readonly property color popupTextColor: "#000000" // цвет текста popup

    readonly property color popupBackgroundColor: "#C5E4FE" // цвет заднего фона popup
    readonly property color popupBorderColor: "#000000" // цвет рамки popup

    //input field
    readonly property color normalInputFieldColor: "#E9E9E9" // цвет обычного поля ввода данных
    readonly property color pressedInputFieldColor: "#E4E4E4" // цвет нажатого поля ввода данных

    readonly property color normalInputFieldTextColor: Qt.rgba(0, 0, 0, 0.25) // цвет текста обычного поля ввода данных
    readonly property color pressedInputFieldTextColor: "#000000" // цвет текста нажатого поля ввода данных

    readonly property color normalInputFieldBorderColor: "transparent" // цвет рамки обычного поля ввода данных
    readonly property color pressedInputFieldBorderColor: "#373737" // цвет рамки нажатого поля ввода данных

    //back button
    readonly property color backgroundBackButtonColor: "transparent" // цвет заднего фона кнопки назад

    //tooltip
    readonly property color toolTipTextColor: "#000000" // цвет текста подсказки

    readonly property color toolTipBorderColor: "#000000" // цвет рамки подскзки
    readonly property color toolTipBackgroundColor: "#C6E5FF" // цвет заднего фона подсказки
}
