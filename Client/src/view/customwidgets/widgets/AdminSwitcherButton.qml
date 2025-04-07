import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../../resources"

Button {
    id: adminSwitcher
    width: Sizes.maxAdminSwitcherButtonWidth // 35
    height: Sizes.maxAdminSwitcherButtonHeight // 35

    property bool isAdmin: false

    Image {
        anchors.fill: parent
        source: adminSwitcher.isAdmin == true ? "qrc:/resources/img/no.svg" : "qrc:/resources/img/yes.svg"
    }

    background: Rectangle {
        color: adminSwitcher.isAdmin == true ? (adminSwitcher.hovered ? Colors.adminSwitcherNoButtonHovered : Colors.adminSwitcherNoButtonNormal) : (adminSwitcher.hovered ? Colors.adminSwitcherYesButtonHovered : Colors.adminSwitcherYesButtonNormal)
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor

        onClicked: {
            parent.clicked()
        }
    }
}
