import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

ListView {
    Control { id: control }
    property real horizontalPadding: 12
    property real verticalPadding: 6
    property real borderWidth: 12
    readonly property int currentAtomicNumber: currentIndex === -1 ? -1 : currentIndex+1
    id: root
    model: AtomListModel {}
    implicitWidth: control.font.pointSize*14+(2*(horizontalPadding+verticalPadding+borderWidth))
    spacing: 6
    delegate: Item {
        id: delegate
        property real borderWidth: ListView.isCurrentItem ? root.borderWidth : 0
        Behavior on borderWidth {
            SmoothedAnimation { duration: 200 }
        }
        implicitWidth: rowLayout.implicitWidth+(2*root.horizontalPadding+borderWidth)
        implicitHeight: rowLayout.implicitHeight+(2*root.verticalPadding)
        Rectangle {
            anchors.fill: parent
            color: control.palette.dark
            opacity: 0.5
        }
        Rectangle {
            anchors.fill: parent
            color: control.palette.light
            opacity: mouseArea.pressed ? 0.3 : mouseArea.containsMouse ? 0.2 : 0.0
        }
        Rectangle {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: delegate.borderWidth/4
            color: control.palette.light
        }
        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: delegate.borderWidth/4
            color: control.palette.light
        }
        RowLayout {
            id: rowLayout
            anchors.centerIn: parent
            Label {
                Layout.preferredWidth: control.font.pointSize*3
                text: atomicNumber
            }
            Rectangle {
                width: control.font.pointSize
                height: control.font.pointSize
                radius: control.font.pointSize
                color: atomicColor
            }
            Label {
                Layout.preferredWidth: control.font.pointSize*8
                text: qsTr("%1u").arg(mass.toFixed(2))
            }
            Label {
                Layout.preferredWidth: control.font.pointSize*4
                text: charge
            }
        }
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: parent.ListView.view.currentIndex = index
        }
    }
}
