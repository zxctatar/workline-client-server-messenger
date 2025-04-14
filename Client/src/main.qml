pragma ComponentBehavior: Bound
import QtQml
import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.platform
import "view/apppages/loginpage"
import "view/apppages/registrationpage"
import "view/apppages/mainpage"
import "view/customwidgets/widgets"
import com.mainController 1.0

ApplicationWindow {
    id: mainWindow


    onClosing: close => {
        close.accepted = false
        hide()
    }

    MainController {
        id: mainController
    }

    SystemTrayIcon {
        id: tray
        visible: true
        icon.source: "qrc:/resources/img/Icon.svg"

        menu: Menu {
            MenuItem {
                text: "Открыть"
                onTriggered: {
                    mainWindow.show()
                    mainWindow.raise()
                    mainWindow.requestActivate()
                }
            }

            MenuItem {
                text: "Закрыть"
                onTriggered: Qt.quit()
            }
        }

        onActivated: {
            mainWindow.show()
            mainWindow.raise()
            mainWindow.requestActivate()
        }
    }

    MyPopup {
        id: popup
        x: (parent.width - width) / 2
        y: 10
    }

    NotificationManager {
        id: notificationManager
        mainWindow: mainWindow
        tray: tray
        popup: popup
    }

    width: 525 // Sizes.maxWindowWidth
    height: 600 // Sizes.maxWindowHeight
    minimumWidth: 525
    minimumHeight: 600
    visible: true
    title: qsTr("WorkLine")

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: loginPage

        Component {
            id:loginPage

            LoginPage {
                controller: mainController.loginPageController
                notificationManager: notificationManager
                onRegisterClicked: {
                    stackView.push(registrationPage)
                }
                onLoginSuccess: {
                    stackView.replace(mainPage)
                }
            }
        }

        Component {
            id: registrationPage
            RegistrationPage {
                controller: mainController.regPageController
                notificationManager: notificationManager
                onBackButtonClicked: {
                    stackView.pop()
                }
            }
        }

        Component {
            id: mainPage
            MainPage {
                mainController: mainController.getMainController()
                notificationManager: notificationManager
            }
        }
    }
}
