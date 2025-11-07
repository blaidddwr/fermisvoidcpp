import "Fermi"
import QtQuick
import QtQuick.Layouts
import internal

Page {
    id: root
    signal activated()
    signal deactivated()
    StackView.onActivating: timer.start()
    StackView.onDeactivating: timer.start()
    Timer {
        id: timer
        interval: root.StackView.view ? root.StackView.view.duration/2 : 0
        repeat: false
        onTriggered: {
            if (root.StackView.status === StackView.Activating) root.activated()
            else root.deactivated()
        }
    }
}
