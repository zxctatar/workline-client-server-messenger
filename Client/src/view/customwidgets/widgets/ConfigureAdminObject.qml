pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "../../../resources"

Item {
    id: configureAdminObject
    height: Sizes.maxAddAdminObjectHeight // 50

    property string displayName
    property string path

    property bool isAdmin

    signal addAdminSignal()
    signal removeAdminSignal()

    RowLayout {
        anchors.fill: parent
        spacing: Sizes.spacingCandidateUserObject // 1

        Rectangle {
            id: recta
            radius: 24
            Layout.preferredWidth: Sizes.maxApplicationObjectImageWidth // 40
            Layout.preferredHeight: Sizes.maxApplicationObjectImageHeight // 40
            Layout.alignment: Qt.AlignVCenter
            color: "transparent"

            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    width: recta.width
                    height: recta.height
                    radius: recta.radius
                }
            }

            Image {
                id: avatar
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                source: configureAdminObject.path == "" ? "qrc:/resources/img/avatar.svg" : configureAdminObject.path
            }
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

