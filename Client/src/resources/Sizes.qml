pragma Singleton
import QtQuick 2.15

QtObject {
    //window
    readonly property int maxWindowWidth: Screen.desktopAvailableWidth // ширина окна
    readonly property int maxWindowHeight: Screen.desktopAvailableHeight // высота окна

    readonly property int windowTextSize: 30 // размер текста окна

    //buttons
    readonly property int maxButtonWidth: 410 // ширина кнопки
    readonly property int maxButtonHeight: 48 // высота кнопки

    readonly property int buttonTextSize: 20 // размер текста кнопки
    readonly property int radiusButtonRectangle: 10 // скругление квадрата кнопки

    //back button
    readonly property int maxBackButtonWidth: 48 // ширина кнопки назад
    readonly property int maxBackButtonHeight: 48 // высота кнопки назад

    readonly property int backButtonLeftMarginSize: 9 // левый отступ кнопки назад
    readonly property int backButtonTopMarginSize: 9 // верхний отступ кнопки назад

    //error text
    readonly property int errorTextSize: 16 // размер текста ошибки

    //input field
    readonly property int maxInputFieldWidth: 410 // ширина поля ввода данных
    readonly property int maxInputFieldHeight: 48 // высота поля ввода данных

    readonly property int leftPaddingSize: 20 // левый отступ поля ввода данных
    readonly property int rightPaddingSize: 20 // правый отступ поля ввода данных
    readonly property int topPaddingSize: 10 // верхний отступ поля ввода данных
    readonly property int bottomPaddingSize: 10 // нижний отступ поля ввода данных

    readonly property int radiusInputFieldRectangle: 10 // скругление квадрата поля ввода данных

    readonly property int inputFieldTextSize: 20 // размер текста поля ввода данных

    //tooltip
    readonly property int maxToolTipWidth: 20 // ширина подсказки
    readonly property int maxToolTipHeight: 20 // высота подсказки

    readonly property int toolTipTextSize: 14 // размер текста подсказки

    readonly property int radiusToolTipSize: 5 // цвет скругления квадрата подсказки
}
