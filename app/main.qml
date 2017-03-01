import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.settings 1.0
import io.github.damaxi 1.0
import "controls" as Controls
import "screens" as Screens

ApplicationWindow {
    id: window
    flags: Qt.Window
    property int current_vocabulary_id: 0

    Component.onCompleted: {
        if (vocabularyBox.model.rowCount() > 0)  {
            vocabularyBox.currentIndex = settings.defaultVocabularyRow
            toolBar.state = ""
        }
        splashScreen.item.state = "StopSplash"
        if (vocabularyBox.model.rowCount() <= 0) {
            configurationPopup.source = "qrc:/controls/ConfigurationPopup.qml"
        }
    }

    Component.onDestruction: {
        settings.defaultVocabularyRow = vocabularyBox.currentIndex
    }

    onClosing: {
        learningScreen.mainModel.submitAll()
    }

    visible: true
    minimumWidth: 1000
    minimumHeight: 800
    title: qsTr("WordFlow")

    Settings {
        id: settings
        property int defaultVocabularyRow: 1
    }

    header: ToolBar {
        id: toolBar
        state: "beforeConfiguration"
        states: [
            State {
                name: "beforeConfiguration"
                PropertyChanges {
                    target: menu
                    visible: false
                }
                PropertyChanges {
                    target: vocabularyBox
                    visible: false
                }
            }
        ]

        ToolButton {
            id: menu
            visible: true
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
            anchors.centerIn: parent
        }

        ComboBox {
            id: vocabularyBox
            function getCurrentId() {
                return  model.getItemId(currentIndex)
            }
            function reload() {
                model.refresh()
                if (currentIndex + 1 > model.rowCount()) currentIndex = 0
            }
            width: 200
            height: toolBar.height
            model: VocabulariesQueryModel { }
            textRole: "name"
            anchors.right: parent.right
            background: Rectangle {
                color: "white"
            }
            onCurrentIndexChanged: {
                window.current_vocabulary_id = getCurrentId()
                learningScreen.reloadWords()
                if (typeof stackView.currentItem.reload == 'function') {
                    stackView.currentItem.reload();
                }
            }

            Material.foreground: Material.Green
            Material.accent: Material.Green
        }
    }

    Controls.Menu {
        id: actionPane
        focus: false
    }

    Pane {
        id: vocabulary
        focus: true
        width: window.width - actionPane.width
        height: window.height - toolBar.height
        anchors.left: actionPane.right
        states: [
            State {
                name: "wider"
                when: !actionPane.visible
                PropertyChanges {
                    target: vocabulary
                    width: window.width
                    anchors.fill: parent
                }
            },
            State {
                name: "narrower"
                when: actionPane.visible
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
            focus: true
            initialItem: Screens.LearningScreen { id: learningScreen }
            pushEnter: Controls.StackViewCommonTransition {}
            popEnter: Controls.StackViewCommonTransition {}
            popExit: Controls.StackViewCommonTransition {}
            pushExit: Controls.StackViewCommonTransition {}
            focusPolicy: Qt.StrongFocus
        }
    }

    Loader {
        id: configurationPopup
        onLoaded: {
            item.open()
        }
    }

    Connections {
        target: configurationPopup.item
        onClosed: {
            vocabularyBox.model.refresh()
            vocabularyBox.currentIndex = settings.defaultVocabularyRow
            toolBar.state = ""
            configurationPopup.source = ""
        }
        onOpened: {
            toolBar.state = "beforeConfiguration"
        }
    }

    Loader {
        id: splashScreen
        source: "qrc:/screens/SplashScreen.qml"
        anchors.fill: parent
    }
}
