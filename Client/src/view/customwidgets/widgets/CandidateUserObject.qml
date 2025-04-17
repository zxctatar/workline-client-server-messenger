pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "../../../resources"

Item {
    id: candidateUserObject
    height: Sizes.maxCandidateUserObjectHeight // 50

    property string displayName
    property string path

    signal addUserClicked()

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
                source: candidateUserObject.path == "" ? "qrc:/resources/img/avatar.svg" : candidateUserObject.path
            }
        }

        MenuText {
            text: candidateUserObject.displayName
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        AddUserButton {
            Layout.preferredWidth: Sizes.maxAddUserButtonWidth // 35
            Layout.preferredHeight: Sizes.maxAddUserButtonHeight // 35
            Layout.rightMargin: Sizes.rightMargineAddUserButton // 5
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

            onClicked: {
                candidateUserObject.addUserClicked()
            }
        }
    }
}



