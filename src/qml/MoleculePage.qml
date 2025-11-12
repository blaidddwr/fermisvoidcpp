import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

CameraPage {
    id: root
    readonly property MoleculeModel model: MoleculeModel {}
    Control { id: control }
    cameraScene: MoleculeScene
    QtObject {
        id: internal
        property real warpRadius: model.radius+0.8
        Behavior on warpRadius {
            SmoothedAnimation {
                velocity: -1
                duration: 400
            }
        }
        onWarpRadiusChanged: MoleculeScene.radius = warpRadius
    }
    StackView.onActivated: moleculeOverlay.visible = true
    StackView.onDeactivating: moleculeOverlay.visible = false
    onActivated: MoleculeScene.setModel(model)
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
    Pane {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 5
        ColumnLayout {
            RowLayout {
                Label {
                    Layout.preferredWidth: largestHeaderLabel.implicitWidth
                    horizontalAlignment: Text.AlignRight
                    text: qsTr("Color:")
                }
                Label {
                    color: root.model.color
                    text: qsTr("%1").arg(root.model.color.toString())
                }
            }
            RowLayout {
                Label {
                    id: largestHeaderLabel
                    Layout.preferredWidth: implicitWidth
                    text: qsTr("Molar Mass:")
                }
                Label { text: qsTr("%1 g/mol").arg(root.model.molarMass) }
            }
            RowLayout {
                Label {
                    Layout.preferredWidth: largestHeaderLabel.implicitWidth
                    horizontalAlignment: Text.AlignRight
                    text: qsTr("Stability:")
                }
                Label { text: qsTr("%1").arg(root.model.stability) }
            }
            RowLayout {
                Label {
                    Layout.preferredWidth: largestHeaderLabel.implicitWidth
                    horizontalAlignment: Text.AlignRight
                    text: qsTr("Charge:")
                }
                Label { text: qsTr("%1").arg(root.model.charge) }
            }
        }
    }
    MoleculeOverlay {
        id: moleculeOverlay
        anchors.fill: parent
        model: root.model
        screenScale: root.screenScale
        hideGUI: root.hideGUI
        visible: false
        onClicked: (position) => { atomListView.position = position }
        onRemoved: atomListView.update()
    }
    AtomListView {
        id: atomListView
        property point position: Qt.point(0,0)
        function update() { atomListAnimation.restart() }
        onPositionChanged: update();
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 5
        visible: !root.hideGUI
        width: implicitWidth
        height: parent.height
        x: root.width-width-5
        model: AtomListModel {}
        clip: true
        indentWidth: -12
        onDoubleClicked: function(atomicNumber) {
            root.model.addAtom(position,atomicNumber)
        }
        SequentialAnimation {
            id: atomListAnimation
            SmoothedAnimation {
                target: atomListView
                property: "x"
                to: root.width
                velocity: -1
                duration: 200
            }
            ScriptAction {
                script: {
                    atomListView.model.atoms = root.model.availableAtoms(atomListView.position)
                    atomListView.currentIndex = atomListView.model.indexOf(
                                moleculeOverlay.currentAtomicNumber
                                )
                }
            }
            SmoothedAnimation {
                target: atomListView
                property: "x"
                to: root.width-atomListView.width-5
                velocity: -1
                duration: 200
            }
        }
    }
}
