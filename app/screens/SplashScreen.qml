import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0

Pane {
    id: splash
    property alias state: indicator.state
    anchors.fill: parent

    RowLayout {
        anchors.centerIn: parent
        BusyIndicator{
            id: indicator
            running: true
            state: "StartSplash"
            states: [
                State {
                    name: "StartSplash"
                    PropertyChanges {
                        target: toolBar
                        opacity: 0
                    }
                },
                State {
                    name: "StopSplash"
                    PropertyChanges {
                        target: toolBar
                        opacity: 1
                    }
                }
            ]
          transitions: [
            Transition {
                from: "StartSplash"; to: "StopSplash"
                NumberAnimation {
                    target: splash
                    properties: "opacity"; to: 0; duration: 2000
//                    onRunningChanged: {
//                        if (!running) {
//                            console.log("Destroying")
//                            splash.deleteLater()
//                        }
//                    }
                }
            }
          ]
        }

        Layout.fillHeight: true
        Layout.fillWidth: true
    }
}
