pragma Singleton
import QtQuick 2.15

QtObject {
    //appwindows
    readonly property int maxWindowWidth: Screen.desktopAvailableWidth // ширина окна
    readonly property int maxWindowHeight: Screen.desktopAvailableHeight // высота окна

    //windows
    readonly property int windowsRadius: 26 // скругление углов окон

    //add image
    readonly property int addImageWidth: 100
    readonly property int addImageHeight: 100

    readonly property int addImageRadius: 50

    //text sizes
    readonly property int bigTextSize: 32
    readonly property int standartTextSize: 16
    readonly property int normalTextSize: 14
    readonly property int smallTextSize: 12

    readonly property int menuTextSize: 20

    //objects image
    readonly property int objectImageWidth: 50
    readonly property int objectImageHeight: 50

    readonly property int chatMessageObjectImageWidth: 45 // ширина аватарки в объекте сообщения
    readonly property int chatMessageObjectImageHeight: 45 // высота автарки в объекте сообщения

    //objects sizes
    readonly property int objectHeight: 50

    readonly property int chatObjectHeight: 70

    readonly property int chatMessageObjectWidth: 450 // ширина сообщения

    //widgets sizes
    readonly property int menuWidgetWidth: 200
    readonly property int menuWidgetHeight: 50

    readonly property int separatorHeight: 1 // высота разделителя

    readonly property int chatInfoBarHeight: 70 // высота панели информации чата

    readonly property int chatBarHeight: 230 // ширина таблицы с чатами

    //buttons sizes
    readonly property int menuButtonWidth: 47 // ширина кнопки меню
    readonly property int menuButtonHeight: 47 // высота кнопки меню

    readonly property int doneButtonWidth: 100 // ширина кнопки готово
    readonly property int doneButtonHeight: 50 // высота кнопки готово

    readonly property int addUserButtonWidth: 35 // ширина кнопки добавления пользователя
    readonly property int addUserButtonHeight: 35 // высота кнопки добавления пользователя

    readonly property int switcherButtonWidth: 35 // ширина кнопки переключения
    readonly property int switcherButtonHeight: 35 // высота кнопки переключения

    readonly property int createChatButtonWidth: 90 // ширина кнопок в окне создании чата
    readonly property int createChatButtonHeight: 40 // высота кнопко в окне создания чата

    //spacings
    readonly property int objectDistance: 15

    readonly property int serverTableSpacing: 15

    readonly property int menuProfilePageSpacing: 3
    readonly property int menuMainPageSpacing: 3 // расстояние между виджетами в главном окне меню

    readonly property int loginPageWidgetsSpacing: 15 // расстояние между виджетами в окне логина

    readonly property int configureAdminObjectSpacing: 10 // отсуп между объектами настройки админа

    readonly property int candidateUserObjectSpacing: 10 // отступ в объекте кандидата на добавление

    readonly property int chatObjectTextSpacing: 8 // расстояние между текстом в объекте чата

    //radius
    readonly property int imageRadius: 24

    readonly property int serverTableWidetRadius: 28 // радиус виджетов объекта сервера

    readonly property int separatorRadius: 2 // скруглдение разделителя

    readonly property int chatMessageObjectRadius: 12 // скругление углов объекта сообщения

    readonly property int createChatButtonRadius: 20 // радиус кнопок в окне создания чата




    //chat message input
    readonly property int chatMessageLeftPadding: 30 // левый отступ текст поля ввода сообщения
    readonly property int chatMessageRightPadding: 30 // правый отступ текста поля ввода сообщения
    readonly property int chatMessageTopPadding: 5 // верхний отступ текста поля ввода сообщения
    readonly property int chatMessageBottomPadding: 5 // нижний отступ текста поля ввода сообщения

    //chat object
    readonly property int chatObjectWidgetSpacing: 10 // расстояние между виджетами в объекте чата
    readonly property int chatObjectMargins: 7 // отступы в объекте чата

    //next button
    readonly property int maxNextButtonWidth: 100 // ширина кнопки далее
    readonly property int maxNextButtonHeight: 50 // высота кнопки далее

    //menu window
    readonly property int maxMenuWindowWidth: 230 // ширина окна меню
    readonly property int maxMenuWindowHeight: 550 // высота окна меню

    readonly property int textTopMargin: 20 // отступ текста сверху в меню

    //select users page
    readonly property int maxSelectUsersPageWidth: 400 // ширина окна выбора пользователей
    readonly property int maxSelectUsersPageHeight: 550 // высота окна выбора пользователей

    //menu profile page
    readonly property int maxMenuProfilePageWidth: 475 // ширина окна профиля меню
    readonly property int maxMenuProfilePageHeight: 550 // высота окна профиля меню

    //menu application page
    readonly property int maxMenuApplicationPageWidth: 475 // ширина окна заявок меню
    readonly property int maxMenuApplicationPageHeight: 550 // высота окна профиля меню

    //menu add user on server page
    readonly property int maxMenuAddUserOnServerPageWidth: 475 // ширина окна добавления пользователя на сервер
    readonly property int maxMenuAddUserOnServerPageHeight: 550 // высота окна добавления пользователя на сервер

    //menu configure admin page
    readonly property int maxMenuConfigureAdminPageWidth: 475 // ширина окна настройки админа
    readonly property int maxMenuConfigureAdminPageHeight: 550 // высота окна настройки админа

    //menu create group chat page
    readonly property int maxMenuCreateGroupChatPageWidth: 475 // ширина окна создания группового чата
    readonly property int maxMenuCreateGroupChatPageHeight: 340 // высота окна создания группового чата

    readonly property int createGroupChatInputFieldWidth: 375 // ширина поля ввода в окне создания группового чата
    readonly property int createGroupChatInputFieldHeight: 40 // высота поля ввода в окне создания группового чата

    readonly property int createGroupChatPageErrorTextWidth: 375 // ширина текста ошибки в окне добавления группового чата

    //refresh button
    readonly property int maxRefreshButtonWidth: 170 // ширина кнопки обновить
    readonly property int maxRefreshButtonHeight: 40 // высота кнопки обновить

    //approve button
    readonly property int maxApproveButtonWidth: 35 // ширина кнопки одобрить
    readonly property int maxApproveButtonHeight: 35 // высота кнопки одобрить

    //reject button
    readonly property int maxRejectButtonWidth: 35 // ширина кнопки отколнить
    readonly property int maxRejectButtonHeight: 35 // высота кнопки отклонить

    //add server window
    readonly property int maxAddServerWindowWidth: 475 // ширина окна добавления сервера
    readonly property int maxAddServerWindowHeight: 550 // высота окна добавления сервера

    //chat info wondow
    readonly property int maxChatInfoWindowWidth: 475 // ширина окна информации чата
    readonly property int maxChatInfoWindowHeight: 550 // высота окна информации чата

    //buttons
    readonly property int maxButtonWidth: 410 // ширина кнопки
    readonly property int maxButtonHeight: 48 // высота кнопки

    readonly property int radiusButtonRectangle: 20 // скругление квадрата кнопки

    //server table
    readonly property int maxServerTableWidth: 78 // ширина таблицы серверов

    //add server button
    readonly property int maxAddServerButtonWidth: 55 // ширина кнопки
    readonly property int maxAddServerButtonHeight: 55 // высота кнопки

    //server object
    readonly property int maxServerObjectWidth: 56 // ширина кнопки объекта сервера
    readonly property int maxServerObjectHeight: 56 // высота кнопки объекта сервера

    //showPasswordButton
    readonly property int maxShowPasswordButtonWidth: 36 // ширина кнопки
    readonly property int maxShowPasswordButtonHeight: 36 // высотка кнопки

    readonly property int showPasswordButtonRightMarginSize: 9 // правый отсутп кнопки показа пароля

    //back button in app
    readonly property int maxBackButtonRegPageWidth: 19 // ширина кнопки назад в приложении
    readonly property int maxBackButtonRegPageHeight: 29 // высота кнопки назад в приложении

    readonly property int backButtonLeftMarginSize: 29 // левый отступ кнопки назад в приложении
    readonly property int backButtonTopMarginSize: 29 // верхний отступ кнопки назад в приложении

    //back button in menu
    readonly property int backButtonLeftMarginSizeMenu: 25 // левый отступ кнопки назад в меню
    readonly property int backButtonTopMarginSizeMenu: 20 // верхний отступ кнопки назад в меню

    //top bar
    readonly property int topBarWidth: 230 // ширина вернего меню
    readonly property int topBarHeight: 70 // высота верхнего меню

    //popup
    readonly property int maxPopupWidth: 400 // ширина popup
    readonly property int maxPopupHeight: 50 // высота popup

    readonly property int radiusPopupSize: 10 // скургление квадрата popup

    //input field
    readonly property int maxInputFieldWidth: 410 // ширина поля ввода данных
    readonly property int maxInputFieldHeight: 48 // высота поля ввода данных

    readonly property int leftPaddingSize: 20 // левый отступ поля ввода данных
    readonly property int rightPaddingSize: 20 // правый отступ поля ввода данных
    readonly property int topPaddingSize: 10 // верхний отступ поля ввода данных
    readonly property int bottomPaddingSize: 10 // нижний отступ поля ввода данных

    readonly property int radiusInputFieldRectangle: 10 // скругление квадрата поля ввода данных

    //tooltip
    readonly property int maxToolTipWidth: 20 // ширина подсказки
    readonly property int maxToolTipHeight: 20 // высота подсказки

    readonly property int radiusToolTipSize: 5 // скругления квадрата подсказки
}
