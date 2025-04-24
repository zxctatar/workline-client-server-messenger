import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import "../../resources"
import "../customwidgets/widgets"

Popup {
    id: addUsersWindow

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    width: 230
    height: 500

    property var controller

    ListView {
        id: listView

        anchors.fill: parent
        spacing: 5
        model: null

        delegate: CandidateUserObject {
            width: parent.width
        }
    }
}
