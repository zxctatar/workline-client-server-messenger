pragma ComponentBehavior: Bound
import QtQuick 2.15
import Qt5Compat.GraphicalEffects

Item {
    id: viewImage

    property int radius: 0
    property string path: ""

    Rectangle {
        id: recta
        anchors.fill: parent
        radius: viewImage.radius
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
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            source: viewImage.path == "" ? "qrc:/resources/img/avatar.svg" : viewImage.path
        }
    }
}
