pragma Singleton
import QtQuick 2.15

QtObject {
    //window
    readonly property int maxWindowWidth: Screen.desktopAvailableWidth // ширина окна
    readonly property int maxWindowHeight: Screen.desktopAvailableHeight // высота окна

    //buttons
    readonly property int maxButtonWidth: 541 // ширина кнопки
    readonly property int maxButtonHeight: 64 // высота кнопки

    //text
    readonly property int windowTextSize: 50 // размер текста окна
    readonly property int buttonTextSize: 26 // размер текста кнопки
    readonly property int inputFieldTextSize: 26 // размер текста поля ввода данных
    readonly property int errorTextSize: 18 // размер текста ошибки

    //input field
    readonly property int maxInputFieldWidth: 541 // ширина поля ввода данных
    readonly property int maxInputFieldHeight: 64 // высота поля ввода данных
}
