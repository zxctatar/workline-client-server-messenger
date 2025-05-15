pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "../../../resources"

Item {
    id: applicationObject
    height: Sizes.objectHeight // 50

    property string displayName
    property string path

    signal approveButtonClicked()
    signal rejectButtonClicked()

    RowLayout {
        anchors.fill: parent
        spacing: 10

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
                source: applicationObject.path == "" ? "qrc:/resources/img/avatar.svg" : applicationObject.path
            }
        }

        MenuText {
            text: applicationObject.displayName
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
        }

        RowLayout {
            spacing: 10

            ApproveButton {
                Layout.preferredWidth: Sizes.maxApproveButtonWidth // 35
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


