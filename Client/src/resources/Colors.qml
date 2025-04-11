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
    readonly property color normalButtonTextColor: "#373737" // цвет текста обычной кнопки

    //chat name text
    readonly property color chatNameTextColor: "#373737" // цвет имени чата

    //admin switcher button
    readonly property color adminSwitcherYesButtonNormal: Qt.rgba(85/255, 206/255, 94/255, 0.50) // обычный цвет кнопки добавить
    readonly property color adminSwitcherYesButtonHovered: Qt.rgba(85/255, 206/255, 94/255, 1) // цвет кнопки добавить когда навелись
    readonly property color adminSwitcherNoButtonNormal: Qt.rgba(255, 0, 0, 0.5) // обычный цвет кнопки убрать
    readonly property color adminSwitcherNoButtonHovered: Qt.rgba(255, 0, 0) // цвет кнопки убрать когда навелись

    //chat message text
    readonly property color chatMessageTextColor: "#373737" // цвет сообщения чата

    //chat object
    readonly property color selectedChatColor: "#1E88E5" // цвет выбранного чата
    readonly property color normalChatColor: "transparent" // цвет не выбранного чата

    //separator
    readonly property color separatorColor: "#B0D5FF" // цвет разделителя

    //add user button
    readonly property color normalAddUserButtonColor: "#9FCCF2" // обычный цвет кнопки добавить пользователя
    readonly property color hoveredAddUserButtonColor: "#52AAF6" // цвет кнопки добавить пользователя когда навелись

    //approve button
    readonly property color hoverApproveButtonColor: Qt.rgba(85/255, 206/255, 94/255, 1) // цвет кнопки одобрить когда навелись
    readonly property color normalApproveButtonColor: Qt.rgba(85/255, 206/255, 94/255, 0.50) // обычный цвет кнопки одобрить

    //reject button
    readonly property color hoverRejectButtonColor: Qt.rgba(255, 0, 0) // цвет кнопки отказать когда навелись
    readonly property color normalRejectButtonColor: Qt.rgba(255, 0, 0, 0.5) // обычный цвет кнопки отказать

    //menu button
    readonly property color menuButtonBackgroundColor: "transparent" // цвет заднего фона кнопки меню

    //menu widget (button)
    readonly property color hoveredMenuWidgetColor: "#C1D7EA" // цвет виджета меню когда навелись
    readonly property color normalMenuWidgetColor: "transparent" // цвет обычного виджета меню

    //top bar
    readonly property color topBarBackgroundColor: "#729EC6" // цвет заднего фона верхнего меню

    //add server button
    readonly property color addServerButtonBackgroundColor: "#5EA9EA" // цвет заднего фона кнопки добавления сервера

    //add server window
    readonly property color addServerWindowBackgroundColor: "#D3E3F1" // цвет заднего фона окна добавления сервера

    //menu window
    readonly property color menuWindowBackgroundColor: "#D3E3F1" // цвет заднего фона окна меню

    //server table
    readonly property color serverTableBackgroundColor: "#0D497D" // цвет заднего фона таблицы серверов

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
