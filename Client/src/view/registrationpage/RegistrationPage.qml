import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../resources"
import "../widgets"

Page {
    id: registrationPage

    signal backButtonClicked()

    background: Rectangle {
        color: Colors.windowBackgroundColor
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
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
        }

        InputField {
            id: inputFieldEmail
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
            placeholderText: "Введите почту"
        }

        InputField {
            id: inputFieldPassword
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
            placeholderText: "Введите пароль"
        }

        InputField {
            id: inputFieldConfirmPassword
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Sizes.maxInputFieldWidth // 410
            Layout.preferredHeight: Sizes.maxInputFieldHeight // 48
            placeholderText: "Повторите пароль"
        }

        ErrorText {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            visible: false

            text: "Неверные данные для входа"
        }

        MyButton {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            Layout.preferredWidth: Sizes.maxButtonWidth // 410
            Layout.preferredHeight: Sizes.maxButtonHeight // 48

            text: "Зарегистрироваться"
        }
    }

    BackButton {
        width: Sizes.maxBackButtonWidth // 48
        height: Sizes.maxBackButtonHeight // 48

        anchors.leftMargin: Sizes.backButtonLeftMarginSize // 9
        anchors.topMargin: Sizes.backButtonTopMarginSize // 9
        anchors.left: parent.left
        anchors.top: parent.top

        onClicked: {
            registrationPage.backButtonClicked()
        }
    }
}
