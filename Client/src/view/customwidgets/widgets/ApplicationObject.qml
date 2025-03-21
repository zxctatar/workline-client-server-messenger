import QtQuick 2.15
import QtQuick.Layouts
import "../../../resources"

Item {
    id: applicationObject
    height: Sizes.maxApplicationObjectHeight // 50

    property string displayName

    signal approveButtonClicked()
    signal rejectButtonClicked()

    RowLayout {
        anchors.fill: parent
        spacing: 10

        Image {
            source: "qrc:/resources/img/avatar.svg"
            Layout.preferredWidth: Sizes.maxApplicationObjectImageWidth // 40
            Layout.preferredHeight: Sizes.maxApplicationObjectImageHeight // 40
        }

        MenuText {
            text: applicationObject.displayName
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
        }

        RowLayout {
            spacing: 5

            ApproveButton {
                Layout.preferredWidth: Sizes.maxApproveButtonWidth //35
                Layout.preferredHeight: Sizes.maxApproveButtonHeight // 35

                onClicked: {
                    applicationObject.approveButtonClicked()
                }
            }

            RejectButton {
                Layout.preferredWidth: Sizes.maxRejectButtonWidth // 35
                Layout.preferredHeight: Sizes.maxRejectButtonHeight // 35

                onClicked: {
                    applicationObject.rejectButtonClicked()
                }
            }
        }
    }
}
