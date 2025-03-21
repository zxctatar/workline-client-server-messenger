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
        spacing: 10

        Image {
            source: "qrc:/resources/img/avatar.svg"
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
        }

        MenuText {
            text: "123123123"
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        AddUserButton {
            Layout.preferredWidth: 35
            Layout.preferredHeight: 35
            Layout.rightMargin: 5
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

            onClicked: {
                candidateUserObject.addUserClicked()
            }
        }
    }
}



