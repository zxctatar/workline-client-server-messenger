import QtQuick 2.15
import QtQuick.Layouts
import "../../../resources"

Item {
    id: configureAdminObject
    height: Sizes.maxAddAdminObjectHeight // 50

    property string displayName

    property bool isAdmin

    signal addAdminSignal()
    signal removeAdminSignal()

    RowLayout {
        anchors.fill: parent
        spacing: Sizes.spacingCandidateUserObject // 1

        Image {
            source: "qrc:/resources/img/avatar.svg"
            Layout.preferredWidth: Sizes.maxCandidateUserObjectImageWidth // 40
            Layout.preferredHeight: Sizes.maxCandidateUserObjectImageHeight // 40
        }

        MenuText {
            text: configureAdminObject.displayName
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        AdminSwitcherButton {
            Layout.preferredWidth: Sizes.maxAddUserButtonWidth // 35
            Layout.preferredHeight: Sizes.maxAddUserButtonHeight // 35
            Layout.rightMargin: Sizes.rightMargineAddUserButton // 5
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

            isAdmin: configureAdminObject.isAdmin

            onClicked: {
                if(isAdmin)
                {
                    configureAdminObject.removeAdminSignal()
                }
                else
                {
                    configureAdminObject.addAdminSignal()
                }
            }
        }
    }
}

