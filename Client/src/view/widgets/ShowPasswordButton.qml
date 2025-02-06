import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../resources"

Button {
    id: showPasswordButton
    width: Sizes.maxShowPasswordButtonWidth // 36
    height: Sizes.maxShowPasswordButtonHeight // 36

    property bool showPassword: false

    Image {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        source: showPasswordButton.showPassword ? "qrc:/resources/img/passwordOn.svg" : "qrc:/resources/img/passwordOff.svg"
    }

    background: Rectangle {
        color: Colors.showPasswordButtonColor
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        cursorShape: Qt.PointingHandCursor

        onClicked: {
            if(showPasswordButton.showPassword)
            {
                showPasswordButton.showPassword = false
            }
            else
            {
                showPasswordButton.showPassword = true
            }

        }
    }
}
