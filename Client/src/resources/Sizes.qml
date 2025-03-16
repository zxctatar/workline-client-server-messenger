pragma Singleton
import QtQuick 2.15

QtObject {
    //window
    readonly property int maxWindowWidth: Screen.desktopAvailableWidth // ширина окна
    readonly property int maxWindowHeight: Screen.desktopAvailableHeight // высота окна

    readonly property int windowTextSize: 30 // размер текста окна

    // login page
    readonly property int loginPageWidgetsSpacing: 18 // расстояние между виджетами в окне логина

    //separator
    readonly property int radiusSeparator: 2 // скруглдение разделителя

    readonly property int separatorHeight: 2 // высота разделителя

    //menu window
    readonly property int maxMenuWindowWidth: 230 // ширина окна меню
    readonly property int maxMenuWindowHeight: 550 // высота окна меню

    readonly property int radiusMenuWindow: 5 // скругление углов окна меню

    readonly property int menuTextSize: 16 // размер текста меню

    //menu main page
    readonly property int mainPageWidgetsSpacing: 3 // расстояние между виджетами в главном окне меню

    //menu profile page
    readonly property int maxMenuProfilePageWidth: 300 // ширина окна профиля меню
    readonly property int maxMenuProfilePageHeight: 550 // высота окна профиля меню

    //menu widget (button)
    readonly property int maxMenuWidgetWidth: 200 // ширина виджета меню
    readonly property int maxMenuWidgetHeight: 50 // высота виджета меню

    //menu button
    readonly property int maxMenuButtonWidth: 47 // ширина кнопки меню
    readonly property int maxMenuButtonHeight: 47 // высота кнопки меню

    //add server window
    readonly property int maxAddServerWindowWidth: 475 // ширина окна добавления сервера
    readonly property int maxAddServerWindowHeight: 550 // высота окна добавления сервера

    readonly property int radiusAddServerWindow: 5 // скругление углов окна добавления сервера

    readonly property int addServerWindowFontSize: 18 // размер шрифта у окна добавления сервера

    //buttons
    readonly property int maxButtonWidth: 410 // ширина кнопки
    readonly property int maxButtonHeight: 48 // высота кнопки

    readonly property int buttonTextSize: 20 // размер текста кнопки
    readonly property int radiusButtonRectangle: 10 // скругление квадрата кнопки

    //server table
    readonly property int serverTableSpacing: 10 // отступ между серверами в таблице серверов

    readonly property int maxServerTableWidth: 78 // ширина таблицы серверов

    //add server button
    readonly property int addServerButtonRadius: 10 // радиус кнопки добавления сервера

    readonly property int maxAddServerButtonWidth: 55 // ширина кнопки
    readonly property int maxAddServerButtonHeight: 55 // высота кнопки

    //server object
    readonly property int serverObjectRadius: 10 // радиус кнопки объекта сервера

    readonly property int maxServerObjectWidth: 55 // ширина кнопки объекта сервера
    readonly property int maxServerObjectHeight: 55 // высота кнопки объекта сервера

    readonly property int serverObjectTextSize: 32 // размер текста у оъекта сервера

    //showPasswordButton
    readonly property int maxShowPasswordButtonWidth: 36 // ширина кнопки
    readonly property int maxShowPasswordButtonHeight: 36 // высотка кнопки

    readonly property int showPasswordButtonRightMarginSize: 9 // правый отсутп кнопки показа пароля

    //back button
    readonly property int maxBackButtonRegPageWidth: 48 // ширина кнопки назад
    readonly property int maxBackButtonRegPageHeight: 48 // высота кнопки назад

    readonly property int backButtonLeftMarginSize: 9 // левый отступ кнопки назад
    readonly property int backButtonTopMarginSize: 9 // верхний отступ кнопки назад

    //error text
    readonly property int errorTextSize: 16 // размер текста ошибки

    //top bar
    readonly property int topBarWidth: 230 // ширина вернего меню
    readonly property int topBarHeight: 60 // высота верхнего меню

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
