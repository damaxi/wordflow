import QtQuick 2.0

Rectangle {
    width: list.width
    height: list.currentItem.height
    color: "#26a837"
    opacity: 0.5
    radius: 5
    y: list.currentItem.y
    Behavior on y {
        SpringAnimation {
            spring: 3
            damping: 0.2
        }
    }
}
