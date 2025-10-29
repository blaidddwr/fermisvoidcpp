import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

Page {
    id: root
    StackView.onActivating: {
        mainPortal.atom.activate()
        mainPortal.atom.setAtom(atomListView.currentAtomicNumber)
        activationAnimation.start()
    }
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
                onClicked: root.StackView.view.pop()
            }
        }
    }
    AtomListView {
        id: atomListView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 5
        model: AtomListModel {}
        clip: true
        AtomModel {
            atomicNumber: atomListView.currentAtomicNumber
            onAtomicNumberChanged: {
                if (atomicNumber === -1) atomInfoLabel.text = ""
                else
                {
                    var text = "";
                    text += qsTr("Atomic Number %1").arg(atomicNumber)
                    text += qsTr(", Atomic Mass %1").arg(mass.toFixed(4))
                    text += qsTr(", Charge %1%2").arg(charge>0?"+":"").arg(charge)
                    atomInfoLabel.text = text
                }
                atomChangeAnimation.restart()
            }
        }
    }
    SequentialAnimation {
        id: atomChangeAnimation
        SmoothedAnimation {
            target: mainPortal
            property: "warp.radius"
            to: 0.0
            velocity: -1
            duration: 200
        }
        ScriptAction {
            script:  mainPortal.atom.setAtom(atomListView.currentAtomicNumber)
        }
        SmoothedAnimation {
            target: mainPortal
            property: "warp.radius"
            to: 1.0
            velocity: -1
            duration: 200
        }
    }
    SmoothedAnimation {
        id: activationAnimation
        target: mainPortal
        property: "warp.radius"
        to: 1.0
        velocity: -1
        duration: 400
    }
}
