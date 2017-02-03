import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4

Pane {
    id: editWordsScreen
    focus: true
    padding: 20
    property var wordsArray: []
    function reload() {
        wordsArray = vocabularyImpl.listWords(window.current_vocabulary_id)
        list.forceActiveFocus() //this is the hack probably something stole focusing
        if (!wordsArray.length) {
            cleanContextPanel()
        }
    }
    function cleanContextPanel() {
        origin.text = ""
        translated.text = ""
    }
    function fillConextPanel() {
        origin.text = wordsArray[list.currentIndex].origin
        translated.text = wordsArray[list.currentIndex].translated
    }
    Component.onCompleted: {
        reload()
    }
    Component {
        id: wordRow
        Column {
            id: delegateRow
            width: editWordsScreen.width - 30
            spacing: 10
            anchors.margins: 10
            Label {
                id: origin
                text: modelData.origin;
                font.pixelSize: 24
                anchors.left: delegateRow.left
                anchors.right: delegateRow.right
                horizontalAlignment: Qt.AlignHCenter
                elide: Text.ElideRight
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        list.currentIndex = index
                        updateButton.checked = true
                        list.lastShowedItem = delegateRow
                        delegateRow.state = "showDetails"
                        updateButton.clicked()
                        contextPanel.forceActiveFocus()
                    }
                }
            }
            Label {
                id: translated
                text: modelData.translated
                visible: false
                font.pixelSize: 24
                anchors.left: delegateRow.left
                anchors.right: delegateRow.right
                horizontalAlignment: Qt.AlignHCenter
                elide: Text.ElideRight
            }
            ProgressBar {
                id: progress
                value: modelData.progress
                visible: false
                from: 0; to: 100
                implicitWidth: delegateRow.width
                anchors.left: delegateRow.left
                anchors.right: delegateRow.right
                anchors.horizontalCenter: delegateRow.Center
                padding: 10
            }
            states: [
                State {
                    name: "showDetails"
                    PropertyChanges {
                        target: translated
                        visible: true
                    }
                    PropertyChanges {
                        target: progress
                        visible: true
                    }
                }
            ]
            Keys.onReturnPressed: {
                updateButton.checked = true
                list.lastShowedItem = delegateRow
                delegateRow.state = "showDetails"
                updateButton.clicked()
                contextPanel.forceActiveFocus()
            }
        }
    }

    Component {
        id: wordHeader
        RowLayout {
            width: editWordsScreen.width - 30
            TextField {
                placeholderText: qsTr("type word")
                font { pixelSize: 28; bold: true }
                Layout.fillWidth: true
            }
        }
    }

    Component {
          id: highlight
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
      }

    ColumnLayout {
        anchors.fill: parent
        focus: true

        ListView {
            id: list
            property var lastShowedItem
            focus: true
            spacing: 5
            height: editWordsScreen.height
            model: editWordsScreen.wordsArray
            header: wordHeader
            delegate: wordRow
            highlight: highlight
            onCurrentIndexChanged: {
                if (typeof list.lastShowedItem !== 'undefined') list.lastShowedItem.state = ""
                contextPanelButtons.uncheckAllAndHide()
            }
        }
    }
    ButtonGroup {
        id: contextPanelButtons
        function uncheckAllAndHide() {
            updateButton.checked = false
            addButton.checked = false
            contextPanel.visible = false
        }
    }
    ColumnLayout {
        anchors.bottom: parent.bottom
        width: editWordsScreen.width - 30
        Keys.onEscapePressed: {
            contextPanelButtons.uncheckAllAndHide()
            list.forceActiveFocus()
        }
        Keys.onDownPressed: {
            list.incrementCurrentIndex()
            list.forceActiveFocus()
        }
        Keys.onUpPressed: {
            list.decrementCurrentIndex()
            list.forceActiveFocus()
        }
        RowLayout {
            Button {
                id: updateButton
                text: qsTr("Update")
                enabled: wordsArray.length > 0
                checkable: true
                Layout.fillWidth: true
                KeyNavigation.tab: origin
                Keys.onReturnPressed: clicked()
                onClicked: {
                    contextPanel.visible = true
                    editWordsScreen.fillConextPanel()
                }
                ButtonGroup.group: contextPanelButtons
            }
            Button {
                id: addButton
                text: qsTr("Add")
                checkable: true
                Layout.fillWidth: true
                KeyNavigation.tab: origin
                Keys.onReturnPressed: clicked()
                onClicked: {
                    contextPanel.visible = true
                    editWordsScreen.cleanContextPanel()
                }
                ButtonGroup.group: contextPanelButtons
            }
            Button {
                id: resetProgressForAll
                text: qsTr("Reset All")
                enabled: wordsArray.length > 0
                Layout.fillWidth: true
                Material.background: "#3faf4d"
                onClicked: {
                    vocabularyImpl.resetProgresses(window.current_vocabulary_id)
                    editWordsScreen.reload()
                    contextPanelButtons.uncheckAllAndHide()
                }
            }
            Button {
                id: deleteAll
                text: qsTr("Delete All")
                enabled: wordsArray.length > 0
                Layout.fillWidth: true
                Material.background: "#3faf4d"
                onClicked: {
                    vocabularyImpl.deleteAll(window.current_vocabulary_id)
                    editWordsScreen.reload()
                    contextPanelButtons.uncheckAllAndHide()
                }
            }
        }
        GridLayout {
            id: contextPanel
            columns: 3; rows: 2
            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: false
            Label {
                text: "Origin"
                font.pixelSize: 20
            }
            TextArea {
                id: origin
                text: ""
                Layout.fillWidth: true
                KeyNavigation.tab: translated
                KeyNavigation.priority: KeyNavigation.BeforeItem
                Layout.columnSpan: 2
            }
            Label {
                text: "Translated"
                font.pixelSize: 20
            }
            TextArea {
                id: translated
                text: ""
                Layout.fillWidth: true
                KeyNavigation.tab: saveButton
                KeyNavigation.priority: KeyNavigation.BeforeItem
                Layout.columnSpan: 2
            }
            RoundButton {
                id: saveButton
                text: "Save"
                Layout.fillWidth: true
                Material.background: Material.Red
                KeyNavigation.tab: deleteButton
                Keys.onReturnPressed: clicked()
                onClicked: {
                    if (updateButton.checked) {
                        vocabularyImpl.updateWord(wordsArray[list.currentIndex].id, origin.text, translated.text)
                        editWordsScreen.reload()
                    } else {
                        vocabularyImpl.createWord(origin.text, translated.text, window.current_vocabulary_id)
                        editWordsScreen.reload()
                    }
                    contextPanelButtons.uncheckAllAndHide()
                }
            }
            RoundButton {
                id: deleteButton
                text: qsTr("Delete")
                enabled: updateButton.checked
                Layout.fillWidth: true
                KeyNavigation.tab: resetProgress
                Keys.onReturnPressed: clicked()
                onClicked: {
                    vocabularyImpl.deleteWord(wordsArray[list.currentIndex].id)
                    editWordsScreen.reload()
                    contextPanelButtons.uncheckAllAndHide()
                }
            }
            RoundButton {
                id: resetProgress
                text: qsTr("Reset Progress")
                enabled: updateButton.checked
                Layout.fillWidth: true
                KeyNavigation.tab: origin
                Keys.onReturnPressed: clicked()
                onClicked: {
                    vocabularyImpl.updateProgress(wordsArray[list.currentIndex].id, 0)
                    editWordsScreen.reload()
                    contextPanelButtons.uncheckAllAndHide()
                }
            }
        }
    }
}
