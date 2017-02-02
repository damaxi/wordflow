import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Styles 1.4

Pane {
    id: learnScreen
    property var wordArray: []
    property int index: 0
    Keys.onLeftPressed: console.log("left")

    function setNewWord() {
        origin.item.text = wordArray[index].origin;
        translated.item.hiddenText = wordArray[index].translated;
    }

    function markWord(progress) {
        vocabularyImpl.updateProgress(wordArray[index].id, progress)
        index += 1
        if (wordArray.length != index) {
            setNewWord()
            translated.hideCard()
        } else {
            index = 0
            reloadWords()
        }
    }

    function reloadWords() {
        learnScreen.wordArray = vocabularyImpl.listWords(window.current_vocabulary_id, 10, true, true)
        translated.hideCard()
        if (wordArray.length != 0) learnScreen.setNewWord();
        else emptyLabel.reloadWordNumber()
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
            font.pixelSize: 28
            hoverEnabled: true
            onHoveredChanged: {
                if (hovered) {
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
                        Material.background: "#41cd52"
                    }
                }
            ]
        }
    }

    ColumnLayout {

        anchors.fill: parent
        spacing: 0

        Label {
            id: emptyLabel
            function reloadWordNumber() {
                wordCount = vocabularyImpl.countWords(window.current_vocabulary_id)
            }
            property int wordCount: vocabularyImpl.countWords(window.current_vocabulary_id)
            visible: wordArray.length ? false : true
            anchors.centerIn: parent
            text: qsTr('Your dictonary is empty. You had learn %1 words.').arg(wordCount)
            font.pixelSize: 24
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
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
            function showCard() {
                item.text = item.hiddenText
                ratingLayout.rateButtonsEnabled = true
            }
            function hideCard() {
                item.text = ""
                ratingLayout.rateButtonsEnabled = false
            }
            visible: wordArray.length ? true : false
            sourceComponent: hoveringButton
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Connections {
            target: translated.item
            onClicked: {
                translated.showCard()
            }
        }

        RowLayout {
            id: ratingLayout
            property bool rateButtonsEnabled: false
            spacing: 20

            Button {
                id: rateAgainButton
                text: qsTr("Again")
                enabled:ratingLayout.rateButtonsEnabled
                visible: wordArray.length ? true : false
                Material.background: "#36703d"
                Layout.fillWidth: true
                checkable: true
                onCheckedChanged: {
                        markWord(25)
                }
            }
            Button {
                id: rateHardButton
                text: qsTr("Hard")
                enabled: ratingLayout.rateButtonsEnabled
                visible: wordArray.length ? true : false
                Layout.fillWidth: true
                Material.background: "#3a8e44"
                checkable: true
                onCheckedChanged: {
                        markWord(50)
                }
            }
            Button {
                id: rateGoodButton
                text: qsTr("Good")
                enabled: ratingLayout.rateButtonsEnabled
                visible: wordArray.length ? true : false
                Layout.fillWidth: true
                Material.background: "#3faf4d"
                checkable: true
                onCheckedChanged: {
                        markWord(75)
                }
            }
            Button {
                id: rateEasyButton
                text: qsTr("Easy")
                enabled: ratingLayout.rateButtonsEnabled
                visible: wordArray.length ? true : false
                Layout.fillWidth: true
                Material.background: "#41cd52"
                checkable: true
                onCheckedChanged: {
                        markWord(100)
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
