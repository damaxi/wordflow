import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.settings 1.0
import "controls" as Controls
import "screens" as Screens

ApplicationWindow {
    id: window
    flags: Qt.Window
    property var vocabularyList: []

    Component.onCompleted: {
        vocabularyImpl.createDatabase()
        if (vocabularyImpl.checkIfVocabularyExist())  {
            window.vocabularyList = vocabularyImpl.listVocabularies()
            vocabularyBox.currentIndex = settings.defaultVocabularyId
            toolBar.state = ""
        }
        splashScreen.item.state = "StopSplash"
        if (!vocabularyImpl.checkIfVocabularyExist()) {
            configurationPopup.source = "qrc:/controls/ConfigurationPopup.qml"
        }
    }

    Component.onDestruction: {
        settings.defaultVocabularyId = vocabularyBox.currentIndex
    }

    visible: true
    Material.theme: Material.Dark
    Material.accent: Material.Red
    minimumWidth: 800
    minimumHeight: 800
    title: qsTr("WordFlow")


    Settings {
        id: settings
        property int defaultVocabularyId: 0
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
            width: 200
            height: toolBar.height
            model: window.vocabularyList
            textRole: "name"
            anchors.right: parent.right
            background: Rectangle {
                color: "white"
            }
            onCurrentIndexChanged: {
                learningScreen.reloadWords()
                //console.log("current index: " + settings.defaultVocabularyId)
                //TODO connect index changing with auto vocabulary learning change
            }

            Material.foreground: Material.Green
            Material.accent: Material.Green
        }
    }

    Controls.Menu {
        id: actionPane
    }

    Pane {
        id: vocabulary
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

            initialItem: Screens.LearningScreen { id: learningScreen }
            pushEnter: Controls.StackViewCommonTransition {}
            popEnter: Controls.StackViewCommonTransition {}
            popExit: Controls.StackViewCommonTransition {}
            pushExit: Controls.StackViewCommonTransition {}
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
            window.vocabularyList = vocabularyImpl.listVocabularies()
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

    //    Drawer {
    //        id: drawer
    //        width: Math.min(window.width, window.height) / 3
    //        height: window.height
    //        visible: true

    //    }
}
