import QtQuick
import QtQuick.Templates as T
import internal

T.StackView {
    id: control
    property real duration: 500
    popEnter: Transition {
        XAnimator {
            from: -control.width
            to: 0
            duration: control.duration
            easing.type: Easing.OutCubic
        }
        SequentialAnimation {
            ScriptAction {
                script: {
                    TransitionScene.x = -1.0
                    TransitionScene.activate()
                }
            }
            SmoothedAnimation {
                target: TransitionScene
                property: "x"
                to: 1.0
                velocity: -1
                duration: control.duration
            }
            ScriptAction { script: TransitionScene.deactivate() }
        }
    }
    popExit: Transition {
        XAnimator {
            from: 0
            to: control.width
            duration: control.duration
            easing.type: Easing.OutCubic
        }
    }
    pushEnter: Transition {
        XAnimator {
            from: control.width
            to: 0
            duration: control.duration
            easing.type: Easing.OutCubic
        }
        SequentialAnimation {
            ScriptAction {
                script: {
                    TransitionScene.x = 1.0
                    TransitionScene.activate()
                }
            }
            SmoothedAnimation {
                target: TransitionScene
                property: "x"
                to: -1.0
                velocity: -1
                duration: control.duration
            }
            ScriptAction { script: TransitionScene.deactivate() }
        }
    }
    pushExit: Transition {
        XAnimator {
            from: 0
            to: -control.width
            duration: control.duration
            easing.type: Easing.OutCubic
        }
    }
    replaceEnter: Transition {
        XAnimator {
            from: control.width
            to: 0
            duration: control.duration
            easing.type: Easing.OutCubic
        }
    }
    replaceExit: Transition {
        XAnimator {
            from: 0
            to: -control.width
            duration: control.duration
            easing.type: Easing.OutCubic
        }
    }
}
