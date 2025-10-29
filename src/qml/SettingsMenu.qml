import "Fermi"
import QtQuick
import QtQuick.Layouts

Page {
    id: root
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
