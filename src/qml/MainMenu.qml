import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

Page {
    id: root
    StackView.onActivating: activationAnimation.start()
    header: Pane {
        Label {
            anchors.centerIn: parent
            text: qsTr("Fermi's Void")
        }
    }
    Pane {
        anchors.centerIn: parent
        Frame {
            ColumnLayout {
                Button {
                    AtomController { id: atomController }
                    text: "Atoms"
                    onClicked: {
                        atomController.generateAtoms()
                        root.StackView.view.push("AtomPage.qml")
                    }
                }
                Button {
                    text: "Settings"
                    onClicked: root.StackView.view.push("SettingsMenu.qml")
                }
                Button {
                    text: "Exit"
                    onClicked: mainWindow.close()
                }
            }
        }
    }
    SequentialAnimation {
        id: activationAnimation
        SmoothedAnimation {
            target: mainPortal
            property: "warp.radius"
            to: 0.0
            velocity: -1
            duration: 400
        }
        ScriptAction {
            script: mainPortal.clearActive()
        }
    }
}
