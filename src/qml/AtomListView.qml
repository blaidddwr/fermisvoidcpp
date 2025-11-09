import "Fermi"
import QtQuick
import QtQuick.Layouts

ListView {
    id: root
    Control { id: control }
    signal doubleClicked(int atomicNumber)
    property real horizontalPadding: 12
    property real verticalPadding: 6
    property real indentWidth: 12
    property bool delegateBackground: true
    readonly property int currentAtomicNumber: {
        currentIndex === -1 ? -1 : model ? model.atomicNumber(currentIndex) : -1
    }
    onCurrentIndexChanged: positionViewAtIndex(currentIndex,ListView.Visible)
    implicitWidth: (control.font.pointSize*16)+(2*horizontalPadding)+Math.abs(indentWidth)+15
    spacing: 6
    delegate: Item {
        id: delegate
        implicitWidth: delegateItem.implicitWidth+Math.abs(root.indentWidth)
        implicitHeight: delegateItem.implicitHeight
        Item {
            id: delegateItem
            x: {
                delegate.ListView.isCurrentItem ?
                root.indentWidth < 0 ? 0 : root.indentWidth
                : root.indentWidth < 0 ? Math.abs(root.indentWidth) : 0
            }
            Behavior on x {
                SmoothedAnimation {
                    velocity: -1
                    duration: 400
                }
            }
            implicitWidth: rowLayout.implicitWidth+(2*root.horizontalPadding)
            implicitHeight: rowLayout.implicitHeight+(2*root.verticalPadding)
            Rectangle {
                anchors.fill: parent
                color: delegate.ListView.isCurrentItem ? control.palette.light : control.palette.dark
                opacity: delegate.ListView.isCurrentItem ? 0.3 : 0.5
                visible: root.delegateBackground || delegate.ListView.isCurrentItem
            }
            Rectangle {
                anchors.fill: parent
                color: control.palette.light
                opacity: mouseArea.pressed ? 0.3 : mouseArea.containsMouse ? 0.2 : 0.0
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
                    text: bonds
                }
            }
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: delegate.ListView.view.currentIndex = index
                onDoubleClicked: root.doubleClicked(atomicNumber)
            }
        }
    }
}
