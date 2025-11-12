import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

Item {
    id: root
    signal clicked(point position)
    signal removed()
    property var model: null
    property int currentAtomicNumber: -1
    property real screenScale: 1
    property bool hideGUI: false
    readonly property point center: Qt.point((width/2),(height/2))
    Control { id: control }
    Repeater {
        id: repeater
        property int currentIndex: 0
        model: root.model
        visible: root.visible
        Item {
            id: delegate
            readonly property bool isCurrentItem: index === repeater.currentIndex
            AtomModel {
                id: atomModel
                atomicNumber: model.atomicNumber
            }
            width: root.screenScale
            height: root.screenScale
            x: root.center.x+((model.x-MoleculeScene.x)*root.screenScale)-(width/2)
            y: root.center.y-((model.y-MoleculeScene.y)*root.screenScale)-(height/2)
            clip: true
            Item {
                anchors.fill: parent
                anchors.margins: 0.05*root.screenScale
                visible: (
                    repeater.visible
                    && !root.hideGUI
                    && width > atomicNumberLabel.width
                    && width > massLabel.width
                    && height > (atomicNumberLabel.height+massLabel.height)
                    )
                Rectangle {
                    anchors.fill: parent
                    color: delegate.isCurrentItem ? control.palette.light : control.palette.dark
                    opacity: delegate.isCurrentItem ? 0.2 : 0.3
                }
                Rectangle {
                    anchors.fill: parent
                    color: control.palette.light
                    opacity: (mouseArea.pressed ?
                        0.3
                        : mouseArea.containsMouse ? 0.2 : 0.0
                        )
                }
                Label {
                    id: atomicNumberLabel
                    anchors.top: parent.top
                    anchors.right: parent.right
                    font.bold: delegate.isCurrentItem
                    text: atomicNumber
                }
                Label {
                    id: massLabel
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    font.bold: delegate.isCurrentItem
                    text: qsTr("%1u").arg(atomModel.mass.toFixed(2))
                }
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton|Qt.RightButton
                    onClicked: function(mouse) {
                        var pos = Qt.point(model.x,model.y)
                        if (repeater.currentIndex !== index)
                        {
                            repeater.currentIndex = index
                            root.currentAtomicNumber = atomicNumber
                            root.clicked(pos)
                        }
                        if (mouse.button === Qt.RightButton)
                        {
                            if (root.model.removeAtom(pos)) root.removed()
                        }
                    }
                }
            }
        }
    }
}
