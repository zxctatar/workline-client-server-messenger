pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "../../../resources"

Item {
    id: addUsersObject
    height: Sizes.maxAddUserObjectHeight // 50

    property string displayName
    property string path

    property bool isSelected: false

    signal addUserSignal()
    signal removeUserSignal()

    RowLayout {
        anchors.fill: parent
        spacing: Sizes.spacingAddUserObject // 10

        Rectangle {
            id: recta
            radius: 24
            Layout.preferredWidth: Sizes.maxAddUserObjectImageWidth // 40
            Layout.preferredHeight: Sizes.maxAddUserObjectImageHeight // 40
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
                source: addUsersObject.path == "" ? "qrc:/resources/img/avatar.svg" : addUsersObject.path
            }
        }

        MenuText {
            text: addUsersObject.displayName
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        SwitcherButton {
            Layout.preferredWidth: Sizes.maxAddUserButtonWidth // 35
            Layout.preferredHeight: Sizes.maxAddUserButtonHeight // 35
            Layout.rightMargin: Sizes.rightMargineAddUserButton // 5
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

            isSelected: addUsersObject.isSelected

            onClicked: {
                if(addUsersObject.isSelected)
                {
                    addUsersObject.removeUserSignal()
                }
                else
                {
                    addUsersObject.addUserSignal()
                }
            }
        }
    }
}

