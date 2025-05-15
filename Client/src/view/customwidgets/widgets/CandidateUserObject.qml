pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "../../../resources"

Item {
    id: candidateUserObject
    height: Sizes.objectHeight // 50

    property string displayName
    property string path

    signal addUserClicked()

    RowLayout {
        anchors.fill: parent
        spacing: Sizes.spacingCandidateUserObject // 1

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
                source: candidateUserObject.path == "" ? "qrc:/resources/img/avatar.svg" : candidateUserObject.path
            }
        }

        MenuText {
            text: candidateUserObject.displayName
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        AddUserButton {
            Layout.preferredWidth: Sizes.addUserButtonWidth // 35
            Layout.preferredHeight: Sizes.addUserButtonHeight // 35
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

            onClicked: {
                candidateUserObject.addUserClicked()
            }
        }
    }
}



