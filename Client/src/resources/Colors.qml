pragma Singleton
import QtQuick 2.15

QtObject {
    //window
    readonly property color windowBackgroundColor: "#DDEFFF" // цвет заднего фона окна

    //buttons
    readonly property color hoverButtonColor: "#1E88E5" // цвет кнопки когда навелись
    readonly property color normalButtonColor: "#4EABFD" // обычный цвет кнопки

    //text
    readonly property color windowTextColor: "#373737" // цвет текста в окне
    readonly property color hoverButtonTextColor: "#292929" // цвет текста кнопки когда навелись
    readonly property color normalButtonTextColor: "#373737" // цвет обычной кнопки
    readonly property color errorTextColor: "#FF0000" // цвет текста ошибки
    readonly property color normalInputFieldTextColor: Qt.rgba(0, 0, 0, 0.25) // цвет текста обычного поля ввода данных
    readonly property color pressedInputFieldTextColor: "#000000" // цвет текста нажатого поля ввода данных

    //input field
    readonly property color normalInputFieldColor: "#E9E9E9" // цвет обычного поля ввода данных
    readonly property color pressedInputFieldColor: "#E4E4E4" // цвет нажатого поля ввода данных

    //border
    readonly property color normalInputFieldBorderColor: "#00000000" // цвет рамки обычного поля ввода данных
    readonly property color pressedInputFieldBorderColor: "#373737" // цвет рамки нажатого поля ввода данных
}
