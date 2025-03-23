import QtQuick 2.15
import QtQuick.Layouts
import "../../../resources"

Item {
    id: candidateUserObject
    height: Sizes.maxCandidateUserObjectHeight // 50

    property string displayName

    signal addUserClicked()

    RowLayout {
        anchors.fill: parent
        spacing: Sizes.spacingCandidateUserObject // 1

        Image {
            source: "qrc:/resources/img/avatar.svg"
            Layout.preferredWidth: Sizes.maxCandidateUserObjectImageWidth // 40
            Layout.preferredHeight: Sizes.maxCandidateUserObjectImageHeight // 40
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



