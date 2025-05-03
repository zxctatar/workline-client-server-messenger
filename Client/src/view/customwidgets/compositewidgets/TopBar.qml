import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"
import "../widgets"
import "../../windows"

Item {
    id: topBar

    width: Sizes.topBarWidth // 230
    height: Sizes.topBarHeight // 70

    property var controller // topBarController

    property var notificationManager // mainPage notificationManager

    Rectangle {
        anchors.fill: parent
        color: Colors.topBarBackgroundColor
    }

    MenuButton {
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            var component = Qt.createComponent("qrc:/view/windows/MenuWindow.qml");
            if(component.status === Component.Ready)
            {
                var menuWindow = component.createObject(topBar, {
                    parent: Overlay.overlay,
                    controller: topBar.controller,
                    notificationManager: topBar.notificationManager
                });

                if(menuWindow) {
                    menuWindow.anchors.centerIn = Overlay.overlay

                    menuWindow.onClosed.connect(function() {
                        menuWindow.destroy();
                    });

                    menuWindow.deleteAll.connect(function() {
                        topBar.controller.deleteProfilePageController()
                        topBar.controller.deleteApplicationPageController()
                        topBar.controller.deleteAddUserOnServerController()
                        topBar.controller.deleteConfigureAdminController()
                        topBar.controller.deleteCreateGroupChatController()
                    });
                }

                menuWindow.open();
            }
        }
    }
}
