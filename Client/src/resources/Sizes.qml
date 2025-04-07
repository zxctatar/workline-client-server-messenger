pragma Singleton
import QtQuick 2.15

QtObject {
    //window
    readonly property int maxWindowWidth: Screen.desktopAvailableWidth // ширина окна
    readonly property int maxWindowHeight: Screen.desktopAvailableHeight // высота окна

    readonly property int windowTextSize: 30 // размер текста окна

    // login page
    readonly property int loginPageWidgetsSpacing: 18 // расстояние между виджетами в окне логина

    // add admin object
    readonly property int maxAddAdminObjectHeight: 50 // высота объекта добавления админа

    // admin switcher button
    readonly property int maxAdminSwitcherButtonWidth: 35 // ширина кнопки переключения админа
    readonly property int maxAdminSwitcherButtonHeight: 35 // высота кнопки переключения админа

    //separator
    readonly property int radiusSeparator: 2 // скруглдение разделителя

    readonly property int separatorHeight: 2 // высота разделителя

    //application object
    readonly property int maxApplicationObjectHeight: 50 // высота объекта заявки

    readonly property int maxApplicationObjectImageWidth: 40 // ширина иконки объекта заявок
    readonly property int maxApplicationObjectImageHeight: 40 // высота иконки объекта заявок

    //candidate user object
    readonly property int maxCandidateUserObjectHeight: 50 // высота объекта кандидата на добавление

    readonly property int maxCandidateUserObjectImageWidth: 40 // ширина иконки объекта заявок
    readonly property int maxCandidateUserObjectImageHeight: 40 // высота иконки объекта заявок

    readonly property int spacingCandidateUserObject: 10 // отступ в объекте кандидата на добавление

    //create Chat Button
    readonly property int maxCreateChatButtonWidth: 75 // ширина кнопок в окне создании чата
    readonly property int maxCreateChatButtonHeight: 30 // высота кнопко в окне создания чата

    readonly property int createChatButtonRadius: 0 // радиус кнопок в окне создания чата

    readonly property int fontPixelSizeCreateChatButton: 14 // размер текста кнопок в окне создания чата

    //add user button
    readonly property int maxAddUserButtonWidth: 35 // ширина кнопки добавления пользователя
    readonly property int maxAddUserButtonHeight: 35 // высота кнопки добавления пользователя

    readonly property int maxAddUserButtonImageWidth: 19 // ширина иконки в кнопке добавления пользователя на сервер
    readonly property int maxAddUserButtonImageHeight: 19 // высота иконки в кнопке добавления пользователя на сервер

    readonly property int rightMargineAddUserButton: 5 // правый отступ в кнопке добавления пользователя на сервер

    //chat name text
    readonly property int chatNameTextSize: 16 // размер текста названия чата

    //chat message text
    readonly property int chatMessageTextSizes: 14 // размер текста сообщения чата

    //chat object
    readonly property int maxChatObjectHeight: 70 // высота объекта чата

    readonly property int maxChatObjectImageWidth: 50 // ширина иконки в объекте чата
    readonly property int maxChatObjectImageHeight: 50 // высота иконки в объекте чата

    readonly property int chatObjectTextSpacing: 8 // расстояние между текстом в объекте чата

    readonly property int chatObjectWidgetSpacing: 10 // расстояние между виджетами в объекте чата
    readonly property int chatObjectMargins: 7 // отступы в объекте чата

    //chats bar
    readonly property int maxChatBarHeight: 230 // ширина таблицы с чатами

    //menu window
    readonly property int maxMenuWindowWidth: 230 // ширина окна меню
    readonly property int maxMenuWindowHeight: 550 // высота окна меню

    readonly property int radiusMenuWindow: 5 // скругление углов окна меню

    readonly property int menuTextSizeInMenu: 20 // размер текста в меню
    readonly property int menuTextSizeInWidgets: 16 // размер текста в виджетах меню

    readonly property int textTopMargin: 10 // отступ текста сверху в меню

    //menu main page
    readonly property int mainPageWidgetsSpacing: 3 // расстояние между виджетами в главном окне меню

    //menu profile page
    readonly property int maxMenuProfilePageWidth: 300 // ширина окна профиля меню
    readonly property int maxMenuProfilePageHeight: 550 // высота окна профиля меню

    //menu application page
    readonly property int maxMenuApplicationPageWidth: 475 // ширина окна заявок меню
    readonly property int maxMenuApplicationPageHeight: 550 // высота окна профиля меню

    readonly property int maxMenuApplicaionPageRefreshButtonWidth: 100 // ширина кнопки обновить в окне заявок
    readonly property int maxMenuApplicaionPageRefreshButtonHeight: 50 // высота кнопки обновить в окне заявок

    //menu add user on server page
    readonly property int maxMenuAddUserOnServerPageWidth: 475 // ширина окна добавления пользователя на сервер
    readonly property int maxMenuAddUserOnServerPageHeight: 550 // высота окна добавления пользователя на сервер

    readonly property int maxMenuAddUserOnServerPageRefreshButtonWidth: 100 // ширина кнопки обновить в добавления пользователя на сервер
    readonly property int maxMenuAddUserOnServerPageRefreshButtonHeight: 50 // высота кнопки обновить в добавления пользователя на сервер

    //menu widget (button)
    readonly property int maxMenuWidgetWidth: 200 // ширина виджета меню
    readonly property int maxMenuWidgetHeight: 50 // высота виджета меню

    //menu button
    readonly property int maxMenuButtonWidth: 47 // ширина кнопки меню
    readonly property int maxMenuButtonHeight: 47 // высота кнопки меню

    //approve button
    readonly property int maxApproveButtonWidth: 35 // ширина кнопки одобрить
    readonly property int maxApproveButtonHeight: 35 // высота кнопки одобрить

    //reject button
    readonly property int maxRejectButtonWidth: 35 // ширина кнопки отколнить
    readonly property int maxRejectButtonHeight: 35 // высота кнопки отклонить

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

    //back button in app
    readonly property int maxBackButtonRegPageWidth: 48 // ширина кнопки назад в приложении
    readonly property int maxBackButtonRegPageHeight: 48 // высота кнопки назад в приложении

    readonly property int backButtonLeftMarginSize: 9 // левый отступ кнопки назад в приложении
    readonly property int backButtonTopMarginSize: 9 // верхний отступ кнопки назад в приложении

    //back button in menu
    readonly property int maxBackButtonMenuWidth: 40 // ширина кнопки назад в меню
    readonly property int maxBackButtonMenuHeight: 40 // высота кнопки назад в меню

    readonly property int backButtonLeftMarginSizeMenu: 7 // левый отступ кнопки назад в меню
    readonly property int backButtonTopMarginSizeMenu: 7 // верхний отступ кнопки назад в меню

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
