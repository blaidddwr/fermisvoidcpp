import "Fermi"
import QtQuick
import QtQuick.Layouts

Page {
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
                    onClicked: mainStackView.pop()
                }
            }
        }
    }
}
