pragma ComponentBehavior: Bound
import QtQml
import QtQuick 2.15
import QtQuick.Controls 2.15
import "view/loginpage"
import "view/registrationpage"
import com.mainController 1.0

ApplicationWindow {
    id: mainWindow

    MainController {
        id: mainController
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
                controller: MainController.loginPageController
                onRegisterClicked: {
                    stackView.push(registrationPage)
                }
            }
        }

        Component {
            id: registrationPage
            RegistrationPage {
                controller: MainController.regPageController
                onBackButtonClicked: {
                    stackView.pop()
                }
            }
        }
    }
}
