import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.settings 1.0
import "controls" as Controls

ApplicationWindow {
    id: window

    Component.onCompleted: {
        vocabularyImpl.createDatabase()
        if (!vocabularyImpl.checkIfVocabularyExist()) {
            configurationPopup.open()
        }
    }

    visible: true
    Material.theme: Material.Dark
    Material.accent: Material.Red
    width: 560
    height: 520
    title: qsTr("WordFlow")

//    Settings {
//        id: settings
//        property string style: "Material"
//    }

    header: ToolBar {
        id: toolBar
        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                id: menu
                contentItem: Image {
                    fillMode: Image.Pad
                    source: "qrc:/images/drawer.png"
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                }
                onClicked: {
                    actionPane.visible = !actionPane.visible
                }
            }

            Label {
                id: titleLabel
                text: "WordFlow"
                font.pixelSize: 20
                //style: Text.Sunken
                //styleColor: "gray"
                //antialiasing: true
                //elide: Label.ElideRight
                anchors.centerIn: parent
                //horizontalAlignment: Qt.AlignHCenter
                //verticalAlignment: Qt.AlignVCenter
                //Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
            }
        }
    }

    Pane {
        id: actionPane
        width: Math.min(window.width, window.height) / 3
        height: window.height //- toolBar.height
        Material.background: Material.Teal

        ColumnLayout {
            spacing: 10
            Material.background: Material.Orange
            anchors.fill: parent
            // Material.foreground: Material.Black
            // Material.elevation: 0

            Button {
                id: learning
                text: qsTr("Start learning")
                anchors.top: parent.top
                Layout.fillWidth: true
                onClicked: {
                    stackView.replace("qrc:/screens/LearningScreen.qml")
                }
            }

            Button {
                text: qsTr("Add new")
                anchors.top: learning.bottom
                Layout.fillWidth: true
                onClicked: {
                    stackView.replace("qrc:/screens/AddNewScreen.qml")
                }
            }
        }
    }

    Pane {
        id: vocabulary
        width: window.width - actionPane.width
        height: window.height - toolBar.height
        anchors.left: actionPane.right
        //Material.background: Material.Lime
        states: [
            State {
                name: "wider"; when: !actionPane.visible
                PropertyChanges {
                    target: vocabulary
                    width: window.width
                    anchors.fill: parent
                }
            },
            State {
                name: "narrower"; when: actionPane.visible
                PropertyChanges {
                    target: vocabulary
                    width: window.width - actionPane.width
                    anchors.left: actionPane.right
                }
            }
        ]

        StackView {
            id: stackView
            anchors.fill: parent

            initialItem: Pane {
                Label {
                    text: qsTr("Your vocabulary is empty")
                    font.pixelSize: 20
                    anchors.centerIn: parent
                    horizontalAlignment: Label.AlignHCenter
                    verticalAlignment: Label.AlignVCenter
                }
            }
        }
    }
    Controls.ConfigurationPopup {
        id: configurationPopup
    }

//    Drawer {
//        id: drawer
//        width: Math.min(window.width, window.height) / 3
//        height: window.height
//        visible: true

//    }
}
