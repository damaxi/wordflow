import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0

Pane {
    width: Math.min(window.width, window.height) / 3
    height: window.height //- toolBar.height
    Material.background: Material.Teal

    Component {
        id: menuButton
        Button {
            Material.background: Material.Orange
        }
    }

    ColumnLayout {
        spacing: 10
        anchors.fill: parent

        //Material.elevation: 0

        Loader {
            id: learning
            sourceComponent:  menuButton
            anchors.top: parent.top
            Layout.fillWidth: true
            onLoaded: {
                item.text = qsTr("Start learning")
            }
        }

        Connections {
            target: learning.item
            onClicked: {
                stackView.replace("qrc:/screens/LearningScreen.qml")
            }
        }

        Loader {
            id: addNewWord
            anchors.top: learning.bottom
            Layout.fillWidth: true
            sourceComponent: menuButton
            onLoaded: {
                item.text = qsTr("Add word")
            }
        }

        Connections {
            target: addNewWord.item
            onClicked: {
                stackView.replace("qrc:/screens/AddNewScreen.qml")
            }
        }

        Loader {
            id: addNewVocabulary
            anchors.top: addNewWord.bottom
            Layout.fillWidth: true
            sourceComponent: menuButton
            onLoaded: {
                item.text = qsTr("Add vocabulary")
            }
        }

        Connections {
            target: addNewVocabulary.item
            onClicked: {
                stackView.replace("qrc:/screens/AddNewVocabularyScreen.qml")
            }
        }
    }
}
