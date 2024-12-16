import QtQuick 2.15
import QtQuick.Controls 2.15
import "view/loginwindow/"

ApplicationWindow {
    id: mainWindow
    width: 640 // Sizes.maxWindowWidth
    height: 480 // Sizes.maxWindowHeight
    visible: true
    title: qsTr("WorkLine")

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: loginWindow
    }

    Component {
        id:loginWindow
        LoginWindow {}
    }

}
