import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

ScenePage {
    id: root
    onActivated: MenuScene.activate()
    onDeactivated: MenuScene.deactivate()
    Component.onCompleted: {
        TransitionScene.color = "#4b2ade"
        MenuScene.color = "#3e009c"
        MenuScene.evColor = "#6600ff"
        MenuScene.activate()
    }
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
}
