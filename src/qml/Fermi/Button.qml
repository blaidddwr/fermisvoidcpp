import QtQuick
import QtQuick.Templates as T

T.Button {
    id: control
    property real borderSize: 1.5
    property real minWidth: 120
    implicitWidth: Math.max(
        implicitBackgroundWidth+leftInset+rightInset,
        implicitContentWidth+leftPadding+rightPadding
        )
    implicitHeight: Math.max(
        implicitBackgroundHeight+topInset+bottomInset,
        implicitContentHeight+topPadding+bottomPadding
        )
    padding: 6
    horizontalPadding: padding+(6*borderSize)+2
    spacing: 6
    contentItem: Label {
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: control.text
        font: control.font
    }
    background: Item {
        implicitWidth: control.minWidth
        Rectangle {
            anchors.fill: parent
            color: control.palette.light
            opacity: control.down ? 0.3 : control.hovered ? 0.2 : 0.1
        }
        Rectangle {
            anchors.left: parent.left
            width: control.visualFocus ? 3*control.borderSize : control.borderSize
            height: parent.height
            color: control.palette.light
        }
        Rectangle {
            anchors.right: parent.right
            width: control.visualFocus ? 3*control.borderSize : control.borderSize
            height: parent.height
            color: control.palette.light
        }
    }
}
