import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../../resources"
import "../../customwidgets/widgets"

Page {
    id: registrationPage

    property var controller // контроллер RegistrationPageController

    property var notificationManager // mainWindow notificationManager

    signal regSuccess()
    signal backButtonClicked()

    background: Rectangle {
        color: Colors.windowBackgroundColor
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            inputFieldLastName.focus = false
            inputFieldFirstName.focus = false
            inputFieldMiddleName.focus = false
            inputFieldLogin.focus = false
            inputFieldPhoneNumber.focus = false
            inputFieldEmail.focus = false
            inputFieldPassword.focus = false
            inputFieldConfirmPassword.focus = false
            inputFieldBirthDate.focus = false
        }
    }

    BackButton {
        id: backButton

        anchors.leftMargin: Sizes.backButtonLeftMarginSize // 29
        anchors.topMargin: Sizes.backButtonTopMarginSize // 29
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            registrationPage.backButtonClicked()
        }
    }

    WindowText {
        id: regText
        anchors.bottom: fields.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 16
        text: "Регистрация"
    }


    Item {
        id: fields
        anchors.centerIn: parent
        anchors.bottom: errorText.top
        width: Sizes.maxInputFieldWidth + 20  // например: 410 + 20 = 430
        height: (Sizes.maxInputFieldHeight * 6) + (16 * 5) + 10 // 6 полей и 5 промежутков

        ScrollView {
            anchors.fill: parent
            width: parent.width
            height: parent.height
            clip: true

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff

            contentItem: Flickable {
                id: flickable
                boundsBehavior: Flickable.StopAtBounds
                contentWidth: coll.width
                contentHeight: coll.height
                interactive: true

                ColumnLayout {
                    id: coll
                    anchors.centerIn: parent
                    spacing: 16
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: Sizes.maxInputFieldWidth

                    AddImage {
                        id: addAvatar
                        Layout.preferredWidth: Sizes.addImageWidth // 100
                        Layout.preferredHeight: Sizes.addImageHeight // 100
                        Layout.alignment: Qt.AlignHCenter
                        radius: Sizes.addImageRadius // 50

                        onBadImage: {
                            errorText.text = "Неверное изображение"
                            errorText.visible = true
                        }

                        onDone: {
                            errorText.visible = false
                        }
                    }

                    RowLayout {
                        Layout.alignment: Qt.AlignHCenter
                        spacing: 2

                        InputField {
                            id: inputFieldLastName
                            Layout.alignment: Qt.AlignHCenter
                            Layout.leftMargin: 10
                            Layout.preferredWidth: 129
                            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
                            placeholderText: "Фамилия"
                        }

                        InputField {
                            id: inputFieldFirstName
                            Layout.alignment: Qt.AlignHCenter
                            Layout.leftMargin: 10
                            Layout.preferredWidth: 129
                            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
                            placeholderText: "Имя"
                        }

                        InputField {
                            id: inputFieldMiddleName
                            Layout.alignment: Qt.AlignHCenter
                            Layout.leftMargin: 10
                            Layout.preferredWidth: 129
                            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
                            placeholderText: "Отчество"
                        }
                    }

                    InputField {
                        id: inputFieldBirthDate
                        Layout.alignment: Qt.AlignHCenter
                        Layout.leftMargin: 10
                        Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
                        Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
                        placeholderText: "Дата рождения (01-01-1999)"

                        validator: RegularExpressionValidator { regularExpression: /^([0][1-9]|[12][0-9]|3[01])-(0[1-9]|1[012])-(19|20)\d\d$/}

                        property string previousText: ""

                        onTextChanged: {
                            if (text.length > previousText.length) {
                                if (text.length === 2 || text.length === 5) {
                                    text += "-"
                                }
                            }

                            previousText = text

                            if (!acceptableInput) {
                                inputFieldBirthDate.color = "red"
                            }
                            else {
                                inputFieldBirthDate.color = "black"
                            }
                        }
                    }

                    InputField {
                        id: inputFieldLogin
                        Layout.alignment: Qt.AlignHCenter
                        Layout.leftMargin: 10
                        Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
                        Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
                        placeholderText: "Логин"
                    }

                    InputField {
                        id: inputFieldPhoneNumber
                        Layout.alignment: Qt.AlignHCenter
                        Layout.leftMargin: 10
                        Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
                        Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
                        placeholderText: "Номер телефона"

                        maximumLength: 11
                        validator: RegularExpressionValidator { regularExpression: /[0-9]+/ }

                        onTextChanged: {
                            if (!acceptableInput) {
                                inputFieldPhoneNumber.color = "red"
                            }
                            else {
                                inputFieldPhoneNumber.color = "black"
                            }
                        }
                    }

                    InputField {
                        id: inputFieldEmail
                        Layout.alignment: Qt.AlignHCenter
                        Layout.leftMargin: 10
                        Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
                        Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
                        placeholderText: "Почта"

                        validator: RegularExpressionValidator { regularExpression: /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/}

                        onTextChanged: {
                            if (!acceptableInput) {
                                inputFieldEmail.color = "red"
                            }
                            else {
                                inputFieldEmail.color = "black"
                            }
                        }
                    }

                    InputField {
                        id: inputFieldPassword
                        Layout.alignment: Qt.AlignHCenter
                        Layout.leftMargin: 10
                        Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
                        Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
                        placeholderText: "Пароль"

                        isPassword: true
                    }

                    InputField {
                        id: inputFieldConfirmPassword
                        Layout.alignment: Qt.AlignHCenter
                        Layout.leftMargin: 10
                        Layout.bottomMargin: 5
                        Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
                        Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
                        placeholderText: "Повторите пароль"

                        isPassword: true
                    }
                }
            }
        }
    }

    ErrorText {
        id: errorText
        anchors.top: fields.bottom
        anchors.topMargin: 16
        width: 410
        anchors.horizontalCenter: parent.horizontalCenter
        visible: false

        text: "Неверные данные для регистрации"
    }

    MyButton {
        id: regButton
        anchors.topMargin: 16
        anchors.top: errorText.visible ? errorText.bottom : fields.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: Sizes.maxButtonWidth // 410
        height: Sizes.maxButtonHeight // 48

        text: "Зарегистрироваться"

        onClicked: {
            if(inputFieldLastName.length <= 0)
            {
                errorText.text = "Введите вашу фамилию"
                errorText.visible = true
                return
            }
            else if(inputFieldFirstName.length <= 0)
            {
                errorText.text = "Введите ваше имя"
                errorText.visible = true
                return
            }
            else if(inputFieldBirthDate.length <= 0)
            {
                errorText.text = "Введите вашу дату рождения"
                errorText.visible = true
                return
            }
            else if(inputFieldBirthDate.length < 10)
            {
                errorText.text = "Введите вашу дату рождения"
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

            registrationPage.controller.prepareRegistrationRequest(addAvatar.encodedFilePath, inputFieldLastName.text, inputFieldFirstName.text, inputFieldMiddleName.text, inputFieldBirthDate.text, inputFieldLogin.text, inputFieldPhoneNumber.text, inputFieldEmail.text, inputFieldPassword.text)
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
            registrationPage.regSuccess()

            return
        }

        function onErrorRegSignal() {
            errorText.visible = false

            registrationPage.notificationManager.showNotificationManager("Регистрация: Ошибка на сервере")

            return
        }
    }
}
