import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../resources"
import "../widgets"

Page {
    id: loginPage

    property var controller // контроллер loginPageController

    signal registerClicked() // сигнал при нажатии на кнопку "Регистрация"

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
        spacing: 18

        WindowText {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Войти"
        }

        InputField {
            id: inputFieldLogin
            Layout.preferredWidth: Sizes.maxInputFieldWidth
            Layout.preferredHeight: Sizes.maxInputFieldHeight
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

        MyButton {
            Layout.preferredWidth: Sizes.maxButtonWidth
            Layout.preferredHeight: Sizes.maxButtonHeight
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Регистрация"

            onClicked: {
                loginPage.registerClicked()
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

        }

        function onAccessDeniedSignal() {
            errorText.text = "Доступ запрещён."
        }

        function onErrorLoginSignal() {

        }
    }
}













