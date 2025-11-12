import "Fermi"
import QtQuick

ScenePage {
    id: root
    property var cameraScene: null
    property real zStepSize: 1.5
    property real cameraDuration: 200
    readonly property bool hideGUI: internal.hideGUI
    readonly property real screenScale: cameraScene.scale*root.height/2
    readonly property point center: Qt.point((width/2),(height/2)-implicitHeaderHeight)
    StackView.onActivating: cameraScene.z = 1.0
    onActivated: {
        cameraScene.x = 0
        cameraScene.y = 0
        cameraScene.activate()
    }
    onDeactivated: {
        cameraScene.dx = 0
        cameraScene.dy = 0
        cameraScene.dz = 0
        cameraScene.deactivate()
    }
    QtObject {
        id: internal
        property bool hideGUI: false
    }
    MouseArea {
        anchors.fill: parent
        onClicked: focus = true
        onWheel: function (mouse)
        {
            focus = true
            if (mouse.angleDelta.y < 0.0) cameraScene.setCameraTarget(
                cameraScene.x+((mouse.x-center.x)/screenScale)
                ,cameraScene.y+((center.y-mouse.y)/screenScale)
                ,cameraScene.z*zStepSize
                ,cameraDuration
                )
            else cameraScene.setCameraTarget(
                cameraScene.x+((mouse.x-center.x)/screenScale)
                ,cameraScene.y+((center.y-mouse.y)/screenScale)
                ,cameraScene.z/zStepSize
                ,cameraDuration)
        }
    }
    Keys.onPressed: function(event) {
        switch (event.key)
        {
        case Qt.Key_H:
            internal.hideGUI = !internal.hideGUI
            event.accepted = true
            return
        case Qt.Key_R:
            cameraScene.setCameraTarget(0,0,1,cameraDuration)
            event.accepted = true
            return
        }
        if (event.isAutoRepeat) return
        switch (event.key)
        {
        case Qt.Key_W:
            cameraScene.dy++
            event.accepted = true
            break
        case Qt.Key_D:
            cameraScene.dx++
            event.accepted = true
            break
        case Qt.Key_S:
            cameraScene.dy--
            event.accepted = true
            break
        case Qt.Key_A:
            cameraScene.dx--
            event.accepted = true
            break
        case Qt.Key_Z:
            cameraScene.dz++
            event.accepted = true
            break
        case Qt.Key_X:
            cameraScene.dz--
            event.accepted = true
            break
        }
    }
    Keys.onReleased: function(event) {
        if (event.isAutoRepeat) return
        switch (event.key)
        {
        case Qt.Key_W:
            cameraScene.dy--
            event.accepted = true
            break
        case Qt.Key_D:
            cameraScene.dx--
            event.accepted = true
            break
        case Qt.Key_S:
            cameraScene.dy++
            event.accepted = true
            break
        case Qt.Key_A:
            cameraScene.dx++
            event.accepted = true
            break
        case Qt.Key_Z:
            cameraScene.dz--
            event.accepted = true
            break
        case Qt.Key_X:
            cameraScene.dz++
            event.accepted = true
            break
        }
    }
}
