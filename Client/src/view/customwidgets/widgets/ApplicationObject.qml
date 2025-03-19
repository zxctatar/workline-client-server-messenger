import QtQuick 2.15
import QtQuick.Layouts
import "../../../resources"

Item {
    id: applicationWidget
    height: Sizes.maxApplicationobjectHeight // 50

    property string displayName

    signal approveButtonClicked()
    signal rejectButtonClicked()

    RowLayout {
        anchors.fill: parent
        spacing: 10 // Расстояние между элементами

        // Аватар
        Image {
            source: "qrc:/resources/img/avatar.svg"
            Layout.preferredWidth: Sizes.maxApplicationObjectImageWidth // 40
            Layout.preferredHeight: Sizes.maxApplicationObjectImageHeight // 40
        }

        // Текст
        MenuText {
            text: applicationWidget.displayName
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
        }

        // Кнопки
        RowLayout {
            spacing: 5 // Расстояние между кнопками

            ApproveButton {
                Layout.preferredWidth: Sizes.maxApproveButtonWidth //35
                Layout.preferredHeight: Sizes.maxApproveButtonHeight // 35

                onClicked: {
                    applicationWidget.approveButtonClicked()
                }
            }

            RejectButton {
                Layout.preferredWidth: Sizes.maxRejectButtonWidth // 35
                Layout.preferredHeight: Sizes.maxRejectButtonHeight // 35

                onClicked: {
                    applicationWidget.rejectButtonClicked()
                }
            }
        }
    }
}
