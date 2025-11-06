import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

Page {
    id: root
    StackView.onActivated: MenuScene.activate()
    StackView.onDeactivated: MenuScene.deactivate()
    header: Pane {
        Label {
            anchors.centerIn: parent
            text: qsTr("Settings")
        }
    }
    Pane {
        anchors.centerIn: parent
        Frame {
            ColumnLayout {
                Button {
                    text: "Back"
                    onClicked: root.StackView.view.pop()
                }
            }
        }
    }
}
