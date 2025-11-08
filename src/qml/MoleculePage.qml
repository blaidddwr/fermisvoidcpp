import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

ScenePage {
    id: root
    property real scale: 100
    readonly property point center: Qt.point(
        (root.width/2)-(0.5*scale)
        ,(root.height/2)-root.implicitHeaderHeight-(0.5*scale)
        )
    header: Pane {
        Label {
            anchors.centerIn: parent
            text: qsTr("Molecule")
        }
    }
    footer: Pane {
        RowLayout
        {
            anchors.fill: parent
            Item { Layout.fillWidth: true }
            Button {
                text: "Back"
                onClicked: root.StackView.view.pop()
            }
        }
    }
    Repeater {
        id: repeater
        property int currentIndex: -1
        model: MoleculeModel {}
        Rectangle {
            id: atomRectangle
            AtomModel {
                id: atomModel
                atomicNumber: model.atomicNumber
            }
            width: 100
            height: 100
            x: root.center.x+model.x*root.scale
            y: root.center.y-model.y*root.scale
            color: atomModel.color
            Rectangle {
                id: atomHighlightRectangle
                anchors.fill: parent
                anchors.margins: 30
                color: "green"
                border.color: "black"
                border.width: 5
                visible: index === repeater.currentIndex
            }
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton|Qt.RightButton
                onClicked: function(mouse) {
                    if (repeater.currentIndex !== index)
                    {
                        repeater.currentIndex = index
                        atomListView.update()
                    }
                    var m = repeater.model
                    if (mouse.button === Qt.RightButton)
                    {
                        var pos = Qt.point(model.x,model.y)
                        if (m.removeAtom(pos)) atomListView.update()
                    }
                    atomListView.atoms = m.availableAtoms(Qt.point(model.x,model.y))
                    atomListView.position = Qt.point(model.x,model.y)
                    atomListView.atomicNumber = atomicNumber
                }
            }
        }
    }
    Item {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
        AtomListView {
            id: atomListView
            property var atoms: Array()
            property point position: Qt.point(0,0)
            property int atomicNumber: -1
            function update() { atomListAnimation.restart() }
            width: implicitWidth
            height: parent.height
            x: -width
            model: AtomListModel { atoms: Array() }
            clip: true
            indentWidth: -12
            onDoubleClicked: function(atomicNumber) {
                repeater.model.addAtom(position,atomicNumber)
            }
            SequentialAnimation {
                id: atomListAnimation
                SmoothedAnimation {
                    target: atomListView
                    property: "x"
                    to: 0.0
                    velocity: -1
                    duration: 200
                }
                ScriptAction {
                    script: {
                        atomListView.model.atoms = atomListView.atoms
                        atomListView.currentIndex = atomListView.model.indexOf(
                                    atomListView.atomicNumber
                                    )
                    }
                }
                SmoothedAnimation {
                    target: atomListView
                    property: "x"
                    to: -atomListView.width
                    velocity: -1
                    duration: 200
                }
            }
        }
    }
}
