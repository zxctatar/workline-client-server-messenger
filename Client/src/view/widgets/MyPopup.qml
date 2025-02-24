import QtQuick 2.15
import QtQuick.Controls 2.15
import "../../resources"

Popup {
    id: popup
    property string popupText

    width: Sizes.maxPopupWidth // 400
    height: Sizes.maxPopupHeight // 50

    background: Rectangle {
        radius: Sizes.radiusPopupSize // 10
        color: Colors.popupBackgroundColor
        border.color: Colors.popupBorderColor
    }

    Label {
        id: label
        anchors.centerIn: parent
        text: popup.popupText
        color: Colors.popupTextColor
        font.family: Fonts.textFont
        font.pixelSize: Sizes.popupTextSize // 20
    }

    Timer {
        interval: 3000
        running: popup.opened
        repeat: false
        onTriggered: popup.close()
    }
}
