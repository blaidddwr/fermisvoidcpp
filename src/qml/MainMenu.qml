import "Fermi"
import QtQuick
import QtQuick.Layouts

Item {
    Pane {
        anchors.centerIn: parent
        ColumnLayout {
            Button {
                text: "New"
            }
            Button {
                text: "Continue"
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
