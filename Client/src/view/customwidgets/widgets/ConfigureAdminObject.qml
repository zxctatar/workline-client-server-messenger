pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "../../../resources"

Item {
    id: configureAdminObject
    height: Sizes.objectHeight // 50

    property string displayName
    property string path

    property bool isAdmin

    signal addAdminSignal()
    signal removeAdminSignal()

    RowLayout {
        anchors.fill: parent
        spacing: Sizes.configureAdminObjectSpacing // 10

        Rectangle {
            id: recta
            radius: 24
            Layout.preferredWidth: Sizes.objectImageWidth // 50
            Layout.preferredHeight: Sizes.objectImageHeight // 50
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

        SwitcherButton {
            Layout.preferredWidth: Sizes.switcherButtonWidth // 35
            Layout.preferredHeight: Sizes.switcherButtonHeight // 35
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

            isSelected: configureAdminObject.isAdmin

            onClicked: {
                if(configureAdminObject.isAdmin)
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

