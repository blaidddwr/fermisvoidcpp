import QtQuick
import QtQuick.Templates as T

T.Pane {
    id: control
    property real borderSize: 1
    implicitWidth: Math.max(
        implicitBackgroundWidth+leftInset+rightInset
        ,implicitContentWidth+leftPadding+rightPadding
        )
    implicitHeight: Math.max(
        implicitBackgroundHeight+topInset+bottomInset
        ,implicitContentHeight+topPadding+bottomPadding
        )
    padding: 12
    background: Item {
        Rectangle {
            anchors.top: parent.top
            width: parent.width
            height: control.borderSize
            color: control.palette.light
        }
        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: control.borderSize
            color: control.palette.light
        }
        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            width: control.borderSize
            height: parent.height/10
            color: control.palette.light
        }
        Rectangle {
            anchors.top: parent.top
            anchors.right: parent.right
            width: control.borderSize
            height: parent.height/10
            color: control.palette.light
        }
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            width: control.borderSize
            height: parent.height/10
            color: control.palette.light
        }
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            width: control.borderSize
            height: parent.height/10
            color: control.palette.light
        }
    }
}
