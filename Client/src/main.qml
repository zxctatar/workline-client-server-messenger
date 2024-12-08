import QtQuick 2.15
import QtQuick.Controls 2.15
import "view/loginwindow"
import "windows"

MyCustomWindow {
    id: mainWindow
    visible: true
    width: 640//Screen.desktopAvailableWidth
    height: 480//Screen.desktopAvailableHeight

    StackView {
        id: stackView
        width: parent.width
        height: parent.height - mainWindow.toolBarHeight

        //initialItem: loginPage
    }

    Component {
        id: loginPage

        LoginWindow {
        }
    }

}
