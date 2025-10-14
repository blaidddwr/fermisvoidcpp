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
    background: Rectangle {
        color: control.palette.dark
        opacity: 0.5
    }
}
