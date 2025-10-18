import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

Page {
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
                    text: "Atoms"
                    onClicked: {
                        Game.start()
                        mainStackView.push("AtomPage.qml")
                    }
                }
                Button {
                    text: "Settings"
                    onClicked: mainStackView.push("SettingsMenu.qml")
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
