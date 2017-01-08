import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4

Pane {
    id: learnScreen
    property var wordArray: []
    property int index: 0

    function setNewWord() {
        origin.item.text = wordArray[index].origin;
        translated.item.hiddenText = wordArray[index].translated;
    }

    function markWord() {

    }

    function setPrevious() {
        if (index == 0) {
            index = wordArray.length - 1;
        } else {
            index -= 1;
        }

        setNewWord();
    }

    function setNext() {
        if (index == wordArray.length - 1) {
            index = 0;
        } else {
            index += 1;
        }

        setNewWord();
    }

    Component {
        id: hoveringButton

        Button {
            id: button
            property string hiddenText: ''
            font.pixelSize: 24
            hoverEnabled: true
            onHoveredChanged: {
                if (hovered && hiddenText.length != 0) {
                    button.state = 'HoveringTranslated'
                } else if (hovered) {
                    button.state = 'Hovering'
                } else {
                    button.state = ''
                }
            }
            states: [
                State {
                    name: "Hovering"
                    PropertyChanges {
                        target: button
                        font.pixelSize: 28
                        Material.background: Material.DeepPurple
                    }
                },
                State {
                    name: "HoveringTranslated"
                    PropertyChanges {
                        target: button
                        font.pixelSize: 28
                        Material.background: Material.DeepOrange
                    }
                }
            ]
        }
    }

    ColumnLayout {

        Component.onCompleted: {
            var current_vocabulary_id = window.vocabularyList[vocabularyBox.currentIndex].id
            learnScreen.wordArray = vocabularyImpl.listWords(current_vocabulary_id, 10)
            if (wordArray.length != 0) learnScreen.setNewWord();
        }

        anchors.fill: parent
        spacing: 0

        Label {
            visible: wordArray.length ? false : true
            text: qsTr('Your dictonary is empty.')
            font.pixelSize: 24
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        Loader {
            id: origin
            visible: wordArray.length ? true : false
            sourceComponent: hoveringButton
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Loader {
            id: translated
            visible: wordArray.length ? true : false
            sourceComponent: hoveringButton
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Connections {
            target: translated.item
            onClicked: {
                translated.item.text = translated.item.hiddenText
                for (var button in ratingButtonGroup.buttons) {
                    button.enabled = true
                    //TODO enable all rating buttons
                }
            }
        }

        ButtonGroup {
            id: ratingButtonGroup
            buttons: ratingLayout.children
        }

        RowLayout {
            id: ratingLayout
            spacing: 20

            Button {
                text: qsTr("Again")
                enabled: false
                Material.background: Material.Red
                Layout.fillWidth: true
                checkable: true
                onCheckedChanged: {
                        if (checked) console.log('dupa')
                }
            }
            Button {
                text: qsTr("Hard")
                enabled: false
                Layout.fillWidth: true
                Material.background: Material.Yellow
                checkable: true
                onCheckedChanged: {
                        if (checked) console.log('dupa')
                }
            }
            Button {
                text: qsTr("Good")
                enabled: false
                Layout.fillWidth: true
                Material.background: Material.Blue
                checkable: true
                onCheckedChanged: {
                        if (checked) console.log('dupa')
                }
            }
            Button {
                text: qsTr("Easy")
                enabled: false
                Layout.fillWidth: true
                Material.background: Material.Green
                checkable: true
                onCheckedChanged: {
                        if (checked) console.log('dupa')
                }
            }
        }

//        RowLayout {
//            id: nextprevLayout
//            spacing: 20
//            visible: wordArray.length ? true : false

//            Button {
//                text: qsTr("Previous")
//                Layout.minimumWidth: parent.width / 2 - nextprevLayout.spacing
//                Layout.fillWidth: true
//                onClicked: learnScreen.setPrevious()
//            }

//            Button {
//                text: qsTr("Next")
//                Layout.minimumWidth: parent.width / 2 - nextprevLayout.spacing
//                Layout.fillWidth: true
//                onClicked: learnScreen.setPrevious()
//            }
//        }
    }
}
