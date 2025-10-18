import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

Page {
    id: root
    StackView.onActivating: atomAnimation.start()
    StackView.onDeactivated: mainPortal.atom.setAtom(-1)
    header: Pane {
        RowLayout {
            anchors.fill: parent
            Item { Layout.fillWidth: true }
            Label {
                text: qsTr("Atom Library")
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
            }
            Item { Layout.fillWidth: true }
        }
    }
    footer: Pane {
        RowLayout
        {
            anchors.fill: parent
            Label {
                id: atomInfoLabel
                Layout.fillWidth: true
            }
            Button {
                text: "Back"
                onClicked: mainStackView.pop()
            }
        }
    }
    AtomListView {
        id: atomListView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 5
        clip: true
        onCurrentAtomicNumberChanged: {
            if (currentAtomicNumber === -1) atomInfoLabel.text = ""
            else
            {
                var atom = model.getAtom(currentAtomicNumber)
                var text = "";
                text += qsTr("Atomic Number %1").arg(atom.atomicNumber)
                text += qsTr(", Atomic Mass %1").arg(atom.mass.toFixed(4))
                text += qsTr(", Charge %1").arg(atom.charge)
                atomInfoLabel.text = text
            }
            atomAnimation.restart()
        }
    }
    SequentialAnimation {
        id: atomAnimation
        SmoothedAnimation {
            target: mainPortal
            property: "warp.radius"
            to: 0.0
            velocity: -1
            duration: 200
        }
        ScriptAction {
            script: {
                if (root.StackView.activating) mainPortal.atom.activate()
                mainPortal.atom.setAtom(atomListView.currentAtomicNumber)
            }
        }
        SmoothedAnimation {
            target: mainPortal
            property: "warp.radius"
            to: mainPortal.atom.radius
            velocity: -1
            duration: 200
        }
    }
}
