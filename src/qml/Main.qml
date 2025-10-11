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
        anchors.fill: parent
        warpColor: "#3e009c"
        evColor: "#6600ff"
        SequentialAnimation on warpRadius {
            NumberAnimation { to: 1; duration: 5000; easing.type: Easing.InOutQuad }
            NumberAnimation { to: 0; duration: 5000; easing.type: Easing.InOutQuad }
            loops: Animation.Infinite
            running: true
        }
    }
    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: MainMenu {}
    }
}
