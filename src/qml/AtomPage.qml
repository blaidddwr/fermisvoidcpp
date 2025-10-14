import "Fermi"
import QtQuick
import QtQuick.Layouts

Page {
    id: root
    StackView.onActivating: atomAnimation.start()
    header: Pane {
        Label {
            anchors.centerIn: parent
            text: qsTr("Atoms")
        }
    }
    footer: Pane {
        Button {
            anchors.right: parent.right
            text: "Back"
            onClicked: mainStackView.pop()
        }
    }
    AtomListView {
        id: atomListView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 5
        clip: true
        onCurrentAtomicNumberChanged: atomAnimation.restart()
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
            script: mainPortal.atom.setAtom(atomListView.currentAtomicNumber)
        }
        SmoothedAnimation {
            target: mainPortal
            property: "warp.radius"
            to: mainPortal.atom.desiredWarpRadius
            velocity: -1
            duration: 200
        }
    }
}
