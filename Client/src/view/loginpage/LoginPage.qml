import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../resources"
import "../widgets"

Page {
    id: loginPage

    signal registerClicked() // сигнал при нажатии на кнопку "Регистрация"

    background: Rectangle {
        color: Colors.windowBackgroundColor
    }

    ColumnLayout {
        anchors.centerIn: parent
        z: 1

        WindowText {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Войти"
        }

        InputField {
            id: inputFieldLogin
            implicitWidth: Sizes.maxInputFieldWidth
            implicitHeight: Sizes.maxInputFieldWidth
            Layout.preferredHeight: Sizes.maxInputFieldHeight
            Layout.topMargin: 35
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            placeholderText: "Логин"
        }

        InputField {
            id: inputFieldPassword
            Layout.preferredWidth: Sizes.maxInputFieldWidth
            Layout.preferredHeight: Sizes.maxInputFieldHeight
            Layout.topMargin: 25
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            placeholderText: "Пароль"

            echoMode: TextInput.Password
        }

        ErrorText {
            visible: false
            Layout.topMargin: 15
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Неверные данные для входа"
        }

        MyButton {
            Layout.preferredWidth: Sizes.maxButtonWidth
            Layout.preferredHeight: Sizes.maxButtonHeight
            Layout.topMargin: 35
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Войти"
        }

        MyButton {
            Layout.preferredWidth: Sizes.maxButtonWidth
            Layout.preferredHeight: Sizes.maxButtonHeight
            Layout.topMargin: 15
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            text: "Регистрация"

            onClicked: {
                loginPage.registerClicked()
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            inputFieldLogin.focus = false
            inputFieldPassword.focus = false
        }
    }
}
