import QtQuick 2.5
import QtQuick.Controls 2.0

Transition {
    OpacityAnimator {
        target: stackView
        from: 0
        to: 1
        duration: 500
    }
}
