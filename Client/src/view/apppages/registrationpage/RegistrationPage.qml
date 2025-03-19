import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../../resources"
import "../../customwidgets/widgets"

Page {
    id: registrationPage

    property var controller // контроллер RegistrationPageController

    property var notificationManager // mainWindow notificationManager

    signal backButtonClicked()

    background: Rectangle {
        color: Colors.windowBackgroundColor
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            inputFieldInitials.focus = false
            inputFieldLogin.focus = false
            inputFieldPhoneNumber.focus = false
            inputFieldEmail.focus = false
            inputFieldPassword.focus = false
            inputFieldConfirmPassword.focus = false
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 18

        RowLayout {
            WindowText {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
                text: "Регистрация"
            }
            Tooltip {
                Layout.preferredWidth: Sizes.maxToolTipWidth // 20
                Layout.preferredHeight: Sizes.maxToolTipHeight // 20
                Layout.alignment: Qt.AlignHCenter

                toolTipText: "Другие данные вы сможете заполнить позднее в профиле"
            }
        }

        InputField {
            id: inputFieldInitials
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
            placeholderText: "ФИО"
        }

        InputField {
            id: inputFieldLogin
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
            placeholderText: "Введите логин"
        }

        InputField {
            id: inputFieldPhoneNumber
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
            placeholderText: "Введите номер телефона"

            maximumLength: 11
            validator: RegularExpressionValidator { regularExpression: /[0-9]+/ }
        }

        InputField {
            id: inputFieldEmail
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
            placeholderText: "Введите почту"

            validator: RegularExpressionValidator { regularExpression: /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/}
        }

        InputField {
            id: inputFieldPassword
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
            placeholderText: "Введите пароль"

            isPassword: true
        }

        InputField {
            id: inputFieldConfirmPassword
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
            placeholderText: "Повторите пароль"

            isPassword: true
        }

        ErrorText {
            id: errorText
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            visible: false

            text: "Неверные данные для регистрации"
        }

        MyButton {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            Layout.preferredWidth: Sizes.maxButtonWidth // 410
            Layout.preferredHeight: Sizes.maxButtonHeight // 48

            text: "Зарегистрироваться"

            onClicked: {
                if(inputFieldInitials.length <= 0)
                {
                    errorText.text = "Введите ваши инициалы"
                    errorText.visible = true
                    return
                }
                else if(inputFieldLogin.length <= 0)
                {
                    errorText.text = "Введите логин"
                    errorText.visible = true
                    return
                }
                else if(inputFieldPhoneNumber.length <= 0)
                {
                    errorText.text = "Введите ваш номер телефона"
                    errorText.visible = true
                    return
                }
                else if(inputFieldPhoneNumber.length < 11)
                {
                    errorText.text = "Номер телефона должен содержать 11 цифр"
                    errorText.visible = true
                    return
                }
                else if(inputFieldEmail.length <= 0)
                {
                    errorText.text = "Введите вашу почту"
                    errorText.visible = true
                    return
                }
                else if(!inputFieldEmail.text.includes("@") || !inputFieldEmail.text.includes("."))
                {
                    errorText.text = "Некорректный адрес почты"
                    errorText.visible = true
                    return
                }
                else if(inputFieldPassword.length < 6)
                {
                    errorText.text = "Введите пароль не менее 6 символов"
                    errorText.visible = true
                    return
                }
                else if(inputFieldPassword.displayText != inputFieldConfirmPassword.displayText)
                {
                    errorText.text = "Пароли не совпадают"
                    errorText.visible = true
                    return
                }

                errorText.visible = false

                registrationPage.controller.prepareRegistrationRequest(inputFieldInitials.text, inputFieldLogin.text, inputFieldPhoneNumber.text, inputFieldEmail.text, inputFieldPassword.text)
            }
        }
    }

    Connections {
        target: registrationPage.controller
        function onLoginExistsSignal() {
            errorText.text = "Данный логин занят"
            errorText.visible = true
            return
        }

        function onPhoneNumberExistsSignal() {
            errorText.text = "Данный номер телефона занят"
            errorText.visible = true
            return
        }

        function onEmailExistsSignal() {
            errorText.text = "Данная почта занята"
            errorText.visible = true
            return
        }

        function onRegOkSignal() {
            errorText.visible = false

            registrationPage.notificationManager.showNotificationManager("Регистрация: Регистрация успешна")

            return
        }

        function onErrorRegSignal() {
            errorText.visible = false

            registrationPage.notificationManager.showNotificationManager("Регистрация: Ошибка на сервере")

            return
        }
    }

    BackButton {
        width: Sizes.maxBackButtonRegPageWidth // 48
        height: Sizes.maxBackButtonRegPageHeight // 48

        anchors.leftMargin: Sizes.backButtonLeftMarginSize // 9
        anchors.topMargin: Sizes.backButtonTopMarginSize // 9
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            registrationPage.backButtonClicked()
        }
    }
}
