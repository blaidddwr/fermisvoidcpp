import "Fermi"
import QtQuick
import QtQuick.Layouts

Item {
    Pane {
        anchors.centerIn: parent
        ColumnLayout {
            Button {
                text: "Back"
                onClicked: mainStackView.pop()
            }
        }
    }
}
