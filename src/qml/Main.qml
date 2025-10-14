import "Fermi"
import QtQuick
import internal

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    font.family: "Monospace"
    palette {
        light: "#00FF00"
        dark: "#000000"
    }
    title: qsTr("Fermi's Void")
    Portal {
        id: mainPortal
        anchors.fill: parent
        warp.color: "#3e009c"
        warp.evColor: "#6600ff"
    }
    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: MainMenu {}
    }
}
