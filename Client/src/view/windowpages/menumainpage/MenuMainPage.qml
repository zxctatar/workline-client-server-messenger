import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: menuMainPage

    property int serverRole: -1
    property string userRole: "none"
    property bool serverSelected: false

    signal profileButtonClicked()
    signal applicationButtonClicked()
    signal addUserOnServerButtonClicked()
    signal configureAdminButtonClicked()
    signal createGroupChatClicked()

    background: Rectangle {
        color: Colors.menuWindowBackgroundColor
    }

    ColumnLayout {
        id: layout
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        spacing: Sizes.mainPageWidgetsSpacing // 3

        MenuWidget {
            Layout.topMargin: 5
            Layout.preferredWidth: menuMainPage.width
            Layout.preferredHeight: Sizes.maxMenuWidgetHeight // 50
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            text: "Профиль"

            onClicked: {
                menuMainPage.profileButtonClicked()
            }
        }

        Separator {
            Layout.fillWidth: true
            visible: menuMainPage.userRole == "admin" ? true : false
        }

        MenuWidget {
            Layout.preferredWidth: menuMainPage.width
            Layout.preferredHeight: Sizes.maxMenuWidgetHeight // 50
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            text: "Заявки"

            visible: menuMainPage.userRole == "admin" ? true : false

            onClicked: {
                menuMainPage.applicationButtonClicked()
            }
        }

        Separator {
            Layout.fillWidth: true
            visible: menuMainPage.userRole == "admin" ? (menuMainPage.serverSelected ? true : false) : false
        }

        MenuWidget {
            Layout.preferredWidth: menuMainPage.width
            Layout.preferredHeight: Sizes.maxMenuWidgetHeight // 50
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            text: "Добавить пользователя"

            visible: menuMainPage.userRole == "admin" ? (menuMainPage.serverSelected ? true : false) : menuMainPage.serverRole == 2 ? (menuMainPage.serverSelected ? true : false) : false

            onClicked: {
                menuMainPage.addUserOnServerButtonClicked()
            }
        }

        Separator {
            Layout.fillWidth: true
            visible: menuMainPage.userRole == "admin" ? (menuMainPage.serverSelected ? true : false) : false
        }

        MenuWidget {
            Layout.preferredWidth: menuMainPage.width
            Layout.preferredHeight: Sizes.maxMenuWidgetHeight // 50
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            text: "Настроить администраторов"

            visible: menuMainPage.userRole == "admin" ? (menuMainPage.serverSelected ? true : false) : false

            onClicked: {
                menuMainPage.configureAdminButtonClicked();
            }
        }

        Separator {
            Layout.fillWidth: true
            visible: menuMainPage.serverSelected ? true : false
        }

        MenuWidget {
            Layout.preferredWidth: menuMainPage.width
            Layout.preferredHeight: Sizes.maxMenuWidgetHeight // 50
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            text: "Создать групповой чат"

            visible: menuMainPage.serverSelected ? true : false

            onClicked: {
                menuMainPage.createGroupChatClicked()
            }
        }
    }
}
