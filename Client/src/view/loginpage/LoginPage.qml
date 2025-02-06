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
            visible: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Неверные данные для входа"
        }

        MyButton {
            Layout.preferredWidth: Sizes.maxButtonWidth
            Layout.preferredHeight: Sizes.maxButtonHeight
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Войти"
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
}
