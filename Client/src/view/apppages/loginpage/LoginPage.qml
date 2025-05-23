    import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../../resources"
import "../../customwidgets/widgets"

Page {
    id: loginPage

    property var controller // контроллер loginPageController

    property var notificationManager // mainWindow notificationManager

    signal registerClicked() // сигнал при нажатии на кнопку "Регистрация"
    signal loginSuccess() // сигнал при успешном входе

    background: Rectangle {
        color: Colors.windowBackgroundColor
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            inputFieldLogin.focus = false
            inputFieldPassword.focus = false
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: Sizes.loginPageWidgetsSpacing // 15

        WindowText {
            Layout.alignment: Qt.AlignHCenter
            text: "Вход"
        }

        InputField {
            id: inputFieldLogin
            Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            placeholderText: "Логин"
        }

        InputField {
            id: inputFieldPassword
            Layout.preferredWidth: Sizes.maxInputFieldWidth
            Layout.preferredHeight: Sizes.maxInputFieldHeight
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            placeholderText: "Пароль"

            isPassword: true
        }

        ErrorText {
            id: errorText
            visible: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Неверные данные для входа"
        }

        MyButton {
            Layout.preferredWidth: Sizes.maxButtonWidth
            Layout.preferredHeight: Sizes.maxButtonHeight
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Войти"

            onClicked: {
                if(inputFieldPassword.length < 6)
                {
                    errorText.text = "Неверный пароль"
                    errorText.visible = true
                    return
                }

                loginPage.controller.prepareLoginRequest(inputFieldLogin.text, inputFieldPassword.text)
            }
        }

        Row {
            Layout.alignment: Qt.AlignHCenter

            Text {
                font.family: Fonts.textFont
                font.weight: Fonts.normalWeight
                font.pixelSize: Sizes.standartTextSize // 16
                color: Colors.windowTextColor
                text: "У вас нет аккаунта? "
            }

            TextButton {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
                text: "Зарегистрироваться"

                onClicked: {
                    loginPage.registerClicked()
                }
            }
        }

    }

    Connections {
        target: loginPage.controller

        function onIncorrectDataSignal() {
            errorText.text = "Неверные данные."
            errorText.visible = true
            return
        }

        function onAccessAllowedSignal() {
            errorText.visible = false
            loginPage.loginSuccess()
            return
        }

        function onAccessDeniedSignal() {
            errorText.visible = false
            loginPage.notificationManager.showNotificationManager("Доступ запрещён.")
            return
        }

        function onErrorLoginSignal() {
            errorText.visible = false
            loginPage.notificationManager.showNotificationManager("Ошибка на сервере.")
            return
        }
    }
}













