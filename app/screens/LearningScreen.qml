import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Styles 1.4
import io.github.damaxi 1.0

Pane {
    id: learnScreen
    property var wordArray: []
    property int index: 0
    property alias mainModel: list.model

    Component.onCompleted: {
        checkIfListNotEmpty()
    }

    function checkIfListNotEmpty() {
        if (list.model.rowCount() <= 0) {
            emptyLabel.words = list.model.countWords()
            learnScreen.state = "EmptyLabel"
            return false
        }
        learnScreen.state = "Default"
        return true
    }

    function markWord(updateProgressCallback) {
        if (list.model.rowCount() - 1 != list.currentIndex) {
            updateProgressCallback();
            list.incrementCurrentIndex()
        } else {
            updateProgressCallback();
            list.model.submitAll();
            if (!checkIfListNotEmpty()) return
            list.currentIndex = 0
        }
    }

    function refresh() {
        list.model.select()
        checkIfListNotEmpty()
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

    Component {
        id: learningRowDelegate

        Column {
            id: delegateItem
            width: list.width; height: list.height

            Loader {
                id: origin
                sourceComponent: hoveringButton
                anchors { right: parent.right; left: parent.left }
                height: delegateItem.height * 4 / 9
                onLoaded: {
                    item.text = model.origin
                }
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
                sourceComponent: hoveringButton
                anchors { right: parent.right; left: parent.left }
                height: delegateItem.height * 4 / 9
                onLoaded: {
                    item.hiddenText = model.translated
                }
            }
            Connections {
                target: translated.item
                onClicked: {
                    translated.showCard()
                }
            }
            RowLayout {
                id: ratingLayout
                anchors { right: parent.right; left: parent.left }
                property bool rateButtonsEnabled: false
                spacing: 20

                Button {
                    id: rateAgainButton
                    text: qsTr("Again")
                    enabled:ratingLayout.rateButtonsEnabled
                    Material.background: "#36703d"
                    Layout.fillWidth: true
                    checkable: true
                    onCheckedChanged: {
                        learnScreen.markWord(function() {
                            list.model.setProgressAgain(list.currentIndex)
                        })
                    }
                }
                Button {
                    id: rateHardButton
                    text: qsTr("Hard")
                    enabled: ratingLayout.rateButtonsEnabled
                    Layout.fillWidth: true
                    Material.background: "#3a8e44"
                    checkable: true
                    onCheckedChanged: {
                        learnScreen.markWord(function() {
                            list.model.setProgressHard(list.currentIndex)
                        })
                    }
                }
                Button {
                    id: rateGoodButton
                    text: qsTr("Good")
                    enabled: ratingLayout.rateButtonsEnabled
                    Layout.fillWidth: true
                    Material.background: "#3faf4d"
                    checkable: true
                    onCheckedChanged: {
                        learnScreen.markWord(function() {
                            list.model.setProgressGood(list.currentIndex)
                        })
                    }
                }
                Button {
                    id: rateEasyButton
                    text: qsTr("Easy")
                    enabled: ratingLayout.rateButtonsEnabled
                    Layout.fillWidth: true
                    Material.background: "#41cd52"
                    checkable: true
                    onCheckedChanged: {
                        learnScreen.markWord(function() {
                            list.model.setProgressEasy(list.currentIndex)
                        })
                    }
                }
            }
        }
    }

    Label {
        id: emptyLabel
        property int words: 0
        visible: false
        anchors.centerIn: parent
        text: qsTr('Your dictonary is empty. You had learn %1 words.').arg(words)
        font.pixelSize: 24
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
    }

    ListView {
        id: list
        anchors.fill: parent
        currentIndex: 0
        model: WordsLearningModel {
            vocabularyfilter: window.current_vocabulary_id;
            onVocabularyfilterChanged: {
                checkIfListNotEmpty();
            }
        }
        delegate: learningRowDelegate
        orientation: ListView.Horizontal
        spacing: 50
    }

    states: [
        State {
            name: "EmptyLabel"
            PropertyChanges {
                target: emptyLabel
                visible: true
            }
            PropertyChanges {
                target: list
                visible: false
            }
        },
        State {
            name: "Default"
            PropertyChanges {
                target: emptyLabel
                visible: false
            }
            PropertyChanges {
                target: list
                visible: true
            }
        }
    ]
}
