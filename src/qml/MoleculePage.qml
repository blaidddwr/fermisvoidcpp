import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

ScenePage {
    id: root
    property real scale: 100
    readonly property point center: Qt.point(
        (root.width/2)-(0.5*scale)
        ,(root.height/2)-root.implicitHeaderHeight-(0.5*scale)
        )
    header: Pane {
        Label {
            anchors.centerIn: parent
            text: qsTr("Molecule")
        }
    }
    footer: Pane {
        RowLayout
        {
            anchors.fill: parent
            Item { Layout.fillWidth: true }
            Button {
                text: "Back"
                onClicked: root.StackView.view.pop()
            }
        }
    }
    Repeater {
        id: repeater
        model: MoleculeModel {}
        Rectangle {
            id: atomRectangle
            AtomModel {
                id: atomModel
                atomicNumber: model.atomicNumber
            }
            width: 100
            height: 100
            x: root.center.x+model.x*root.scale
            y: root.center.y+model.y*root.scale
            color: atomModel.color
            MouseArea {
                anchors.fill: parent
                onClicked: repeater.model.addAtom(Qt.point(model.x,model.y),1)
            }
        }
    }
}
