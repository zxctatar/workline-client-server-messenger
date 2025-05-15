pragma Singleton
import QtQuick 2.15

QtObject {
    //window
    readonly property color windowBackgroundColor: "#F2F2F2" // цвет заднего фона окна

    readonly property color windowTextColor: "#383C45" // цвет текста в окне

    //buttons
    readonly property color hoverButtonColor: "#78A095" // цвет кнопки когда навелись
    readonly property color normalButtonColor: "#383C45" // обычный цвет кнопки

    readonly property color hoverButtonTextColor: "#FFFFFF" // цвет текста кнопки когда навелись
    readonly property color normalButtonTextColor: "#EAEAEA" // цвет текста обычной кнопки

    //chats bar
    readonly property color chatsBarBackgroundColor: "#576172" // задний фон таблицы чатов

    //text button
    readonly property color textButtonNormalTextColor: "#1E88E5" // нормальный цвет кнопки
    readonly property color textButtonHoveredTextColor: "#1E88E5" // цвет кнопки при наведении

    //add image
    readonly property color addImageHoveredBackgroundColor: "#FFFFFF" // задний фон поля добавления фото при наведении
    readonly property color addImageNormalBackgroundColor: "#F2F2F2" // нормальный задний фон поля добавления фото

    readonly property color addImageHoveredBorderColor: "#383C45" // цвет рамки поля добавления фото когда навелись
    readonly property color addImageNormalBorderColor: "#838892" // нормальный цвет рамки поля добавления фото

    //chat name text
    readonly property color chatNameTextColor: "#F2F2F2" // цвет имени чата

    //chat message object
    readonly property color chatMessageCandidateColor: "#576172" // цвет сообщения собеседника
    readonly property color chatMessageUserColor: "#383C45" // цвет собственного сообщения

    //chat message text
    readonly property color chatMessageTextColor: "#F2F2F2" // цвет сообщения чата

    //chat last message text
    readonly property color chatLastMessageTextColor: "#BEBEBE" // цвет последнего сообщения чата в таблице чатов

    //chat object
    readonly property color selectedChatColor: "#383C45" // цвет выбранного чата
    readonly property color hoveredChatColor: "#6F7B8E" // цвет чата когда навелись
    readonly property color normalChatColor: "transparent" // цвет не выбранного чата

    //separator
    readonly property color separatorColor: "#556370" // цвет разделителя

    //menu button
    readonly property color menuButtonBackgroundColor: "transparent" // цвет заднего фона кнопки меню

    //menu widget (button)
    readonly property color normalMenuWidgetColor: "transparent" // цвет обычного виджета меню

    readonly property color menuWidgetTextColor: "#000000" // цвет текста виджета меню

    //top bar
    readonly property color topBarBackgroundColor: "#576172" // цвет заднего фона верхнего меню

    //chat info bar
    readonly property color chatInfoBarBackgroundColor: "#383C45" // цвет заднего фона панели информации чата

    //add server button
    readonly property color addServerButtonBackgroundColor: "transparent" // цвет заднего фона кнопки добавления сервера

    //add server window
    readonly property color addServerWindowBackgroundColor: "#F2F2F2" // цвет заднего фона окна добавления сервера

    //menu window
    readonly property color menuWindowBackgroundColor: "#F2F2F2" // цвет заднего фона окна меню

    //server table
    readonly property color serverTableBackgroundColor: "#383C45" // цвет заднего фона таблицы серверов

    //show password button
    readonly property color showPasswordButtonColor: "transparent" // цвет заднего фона кнопки показа пароля

    //error text
    readonly property color errorTextColor: "#FF0000" // цвет текста ошибки

    //popup
    readonly property color popupTextColor: "#383C45" // цвет текста popup

    readonly property color popupBackgroundColor: "#DADADA" // цвет заднего фона popup
    readonly property color popupBorderColor: "#383C45" // цвет рамки popup

    //input field
    readonly property color normalInputFieldColor: "#F2F2F2" // цвет обычного поля ввода данных
    readonly property color pressedInputFieldColor: "#FFFFFF" // цвет нажатого поля ввода данных

    readonly property color normalInputFieldTextColor: "#556370" // цвет текста обычного поля ввода данных
    readonly property color pressedInputFieldTextColor: "#000000" // цвет текста нажатого поля ввода данных

    readonly property color normalInputFieldBorderColor: "#838892" // цвет рамки обычного поля ввода данных
    readonly property color pressedInputFieldBorderColor: "#383C45" // цвет рамки нажатого поля ввода данных

    //back button
    readonly property color backgroundBackButtonColor: "transparent" // цвет заднего фона кнопки назад

    //tooltip
    readonly property color toolTipTextColor: "#000000" // цвет текста подсказки

    readonly property color toolTipBorderColor: "#000000" // цвет рамки подскзки
    readonly property color toolTipBackgroundColor: "#C6E5FF" // цвет заднего фона подсказки
}
