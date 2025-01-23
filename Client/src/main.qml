pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15
import com.example.mainController 1.1
import "view/loginpage"
import "view/registrationpage"

ApplicationWindow {
    id: mainWindow
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
                onRegisterClicked: {
                    stackView.push(registrationPage)
                }
            }
        }

        Component {
            id: registrationPage
            RegistrationPage {
                onBackButtonClicked: {
                    stackView.pop()
                }
            }
        }
    }
}
