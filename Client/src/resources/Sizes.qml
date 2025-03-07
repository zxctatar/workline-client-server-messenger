pragma Singleton
import QtQuick 2.15

QtObject {
    //window
    readonly property int maxWindowWidth: Screen.desktopAvailableWidth // ширина окна
    readonly property int maxWindowHeight: Screen.desktopAvailableHeight // высота окна

    readonly property int windowTextSize: 30 // размер текста окна

    // login page
    readonly property int loginPageWidgetsSpacing: 18 // расстояние между виджетами в окне логина

    //buttons
    readonly property int maxButtonWidth: 410 // ширина кнопки
    readonly property int maxButtonHeight: 48 // высота кнопки

    readonly property int buttonTextSize: 20 // размер текста кнопки
    readonly property int radiusButtonRectangle: 10 // скругление квадрата кнопки

    //add server button
    readonly property int addServerButtonRadius: 10 // радиус кнопки добавления сервера

    //showPasswordButton
    readonly property int maxShowPasswordButtonWidth: 36 // ширина кнопки
    readonly property int maxShowPasswordButtonHeight: 36 // высотка кнопки

    readonly property int showPasswordButtonRightMarginSize: 9 // правый отсутп кнопки показа пароля

    //back button
    readonly property int maxBackButtonWidth: 48 // ширина кнопки назад
    readonly property int maxBackButtonHeight: 48 // высота кнопки назад

    readonly property int backButtonLeftMarginSize: 9 // левый отступ кнопки назад
    readonly property int backButtonTopMarginSize: 9 // верхний отступ кнопки назад

    //error text
    readonly property int errorTextSize: 16 // размер текста ошибки

    //popup
    readonly property int maxPopupWidth: 400 // ширина popup
    readonly property int maxPopupHeight: 50 // высота popup

    readonly property int popupTextSize: 16 // размер текста popup

    readonly property int radiusPopupSize: 10 // скургление квадрата popup

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

    readonly property int radiusToolTipSize: 5 // скругления квадрата подсказки
}
