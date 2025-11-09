import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

ScenePage {
    id: root
    Control { id: control }
    readonly property MoleculeModel model: MoleculeModel {}
    readonly property real screenScale: MoleculeScene.screenScale
    readonly property point center: Qt.point(
        (width/2)-(0.5*screenScale)
        ,(height/2)-implicitHeaderHeight-(0.5*screenScale)
        )
    property real sceneScale: 0.5
    property real scaleStepFactor: 1.5
    property real scrollSpeed: 1.0/sceneScale
    property bool hideGUI: false
    QtObject {
        id: internal
        property real warpRadius: model.radius+0.8
        property real dx: 0.0
        property real dy: 0.0
        Behavior on warpRadius {
            SmoothedAnimation {
                velocity: -1
                duration: 400
            }
        }
        onWarpRadiusChanged: MoleculeScene.radius = warpRadius
        onDxChanged: MoleculeScene.dx = root.scrollSpeed*dx
        onDyChanged: MoleculeScene.dy = root.scrollSpeed*dy
    }
    Behavior on sceneScale { NumberAnimation { duration: 200 } }
    onSceneScaleChanged: MoleculeScene.scale = sceneScale
    onScrollSpeedChanged: {
        MoleculeScene.dx = scrollSpeed*internal.dx
        MoleculeScene.dy = scrollSpeed*internal.dy
    }
    StackView.onActivated: repeater.visible = true
    StackView.onActivating: MoleculeScene.scale = sceneScale
    StackView.onDeactivating: repeater.visible = false
    onActivated: {
        MoleculeScene.x = 0
        MoleculeScene.y = 0
        MoleculeScene.dx = 0
        MoleculeScene.dy = 0
        MoleculeScene.setModel(model)
        MoleculeScene.activate()
    }
    onDeactivated: {
        MoleculeScene.dx = 0
        MoleculeScene.dy = 0
        MoleculeScene.deactivate()
    }
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
    MouseArea {
        anchors.fill: parent
        onClicked: focus = true
        onWheel: function (mouse)
        {
            focus = true
            sceneScale = (mouse.angleDelta.y < 0.0 ?
                sceneScale/root.scaleStepFactor
                : sceneScale*root.scaleStepFactor
                )
        }
    }
    Keys.onPressed: function(event) {
        if (event.key === Qt.Key_H)
        {
            root.hideGUI = !root.hideGUI
            return
        }
        if (event.isAutoRepeat) return
        switch (event.key)
        {
        case Qt.Key_W:
            internal.dy++
            event.accepted = true
            break;
        case Qt.Key_D:
            internal.dx++
            event.accepted = true
            break;
        case Qt.Key_S:
            internal.dy--
            event.accepted = true
            break;
        case Qt.Key_A:
            internal.dx--
            event.accepted = true
            break;
        }
    }
    Keys.onReleased: function(event) {
        if (event.isAutoRepeat) return
        switch (event.key)
        {
        case Qt.Key_W:
            internal.dy--
            event.accepted = true
            break;
        case Qt.Key_D:
            internal.dx--
            event.accepted = true
            break;
        case Qt.Key_S:
            internal.dy++
            event.accepted = true
            break;
        case Qt.Key_A:
            internal.dx++
            event.accepted = true
            break;
        }
    }
    Repeater {
        id: repeater
        property int currentIndex: 0
        model: root.model
        visible: false
        Item {
            id: delegate
            readonly property bool isCurrentItem: index === repeater.currentIndex
            AtomModel {
                id: delegateAtomModel
                atomicNumber: model.atomicNumber
            }
            width: root.screenScale
            height: root.screenScale
            x: root.center.x+((model.x-MoleculeScene.x)*root.screenScale)
            y: root.center.y-((model.y-MoleculeScene.y)*root.screenScale)
            clip: true
            Item {
                anchors.fill: parent
                anchors.margins: 0.05*root.screenScale
                visible: (
                    repeater.visible
                    && !root.hideGUI
                    && width > delegateAtomicNumberLabel.width
                    && width > delegateMassLabel.width
                    && height > (delegateAtomicNumberLabel.height+delegateMassLabel.height)
                    )
                Rectangle {
                    anchors.fill: parent
                    color: delegate.isCurrentItem ? control.palette.light : control.palette.dark
                    opacity: delegate.isCurrentItem ? 0.2 : 0.3
                }
                Rectangle {
                    anchors.fill: parent
                    color: control.palette.light
                    opacity: (delegateMouseArea.pressed ?
                        0.3
                        : delegateMouseArea.containsMouse ? 0.2 : 0.0
                        )
                }
                Label {
                    id: delegateAtomicNumberLabel
                    anchors.top: parent.top
                    anchors.right: parent.right
                    font.bold: delegate.isCurrentItem
                    text: atomicNumber
                }
                Label {
                    id: delegateMassLabel
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    font.bold: delegate.isCurrentItem
                    text: qsTr("%1u").arg(delegateAtomModel.mass.toFixed(2))
                }
                MouseArea {
                    id: delegateMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton|Qt.RightButton
                    onClicked: function(mouse) {
                        if (repeater.currentIndex !== index)
                        {
                            repeater.currentIndex = index
                            atomListView.update()
                        }
                        var m = root.model
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
    }
    Item {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
        visible: !root.hideGUI
        AtomListView {
            id: atomListView
            property var atoms: root.model.availableAtoms(position)
            property point position: Qt.point(0,0)
            property int atomicNumber: -1
            function update() { atomListAnimation.restart() }
            width: implicitWidth
            height: parent.height
            x: -width
            model: AtomListModel { atoms: atomListView.atoms }
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
