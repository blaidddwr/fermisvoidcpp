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
    Component.onCompleted: {
        MenuScene.color = "#3e009c"
        MenuScene.evColor = "#6600ff"
    }
    Portal {
        id: mainPortal
        anchors.fill: parent
    }
    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: MainMenu {}
    }
}
