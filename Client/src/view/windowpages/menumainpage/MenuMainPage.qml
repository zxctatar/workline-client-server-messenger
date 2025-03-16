import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../../customwidgets/widgets"
import "../../../resources"

Page {
    id: menuMainPage

    property string userRole

    signal profileButtonClicked()

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
        }

        MenuWidget {
            Layout.preferredWidth: menuMainPage.width
            Layout.preferredHeight: Sizes.maxMenuWidgetHeight // 50
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            text: "Заявки"

            visible: menuMainPage.userRole == "admin" ? true : false
        }
    }
}
