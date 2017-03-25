import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Styles 1.4
import io.github.damaxi 1.0

Pane {
    GridLayout {
        id: translateGrid
        anchors.fill: parent
        anchors.rightMargin: 25
        columns: 2; rows: 4
        columnSpacing: 30

        Component.onCompleted: {
            from.currentIndex = settings.sourceLangTranslator
            to.currentIndex = settings.destinationLangTranslator
            wordsEditModel.select()
        }

        Component.onDestruction: {
            settings.sourceLangTranslator = from.currentIndex
            settings.destinationLangTranslator = to.currentIndex
        }

        Component {
            id: textArea

            TextArea {
                text: ""
                font.pixelSize: 25
                color: "black"
                padding: 20
                mouseSelectionMode: TextEdit.SelectWords
                selectByMouse: true
                background: Rectangle {
                    color: !readOnly ? "white" : "#7c7878"
                    border.color: focus ? "#32dd02" : "#166906"
                    border.width: 2
                }
            }
        }

        Translate {
            id: translate
            onNotifyTranslated: {
                translatedWord.item.text = translated
            }
        }

        WordsEditModel {
            id: wordsEditModel
        }

        RowLayout {
            spacing: 10
            ComboBox {
                id: from
                model: translate.listSupportedLanguages()
                font.pixelSize: 20
                onCurrentTextChanged: {
                    translate.source = currentText
                    translate.word = sourceWord.item.text
                }
                Layout.fillWidth: true
            }
            Button {
                font.pixelSize: 20
                text: "Swap"
                Material.background: Material.Red
                onClicked: {
                    var temp = from.currentIndex
                    from.currentIndex = to.currentIndex
                    to.currentIndex = temp
                }
            }
            ComboBox {
                id: to
                model: translate.listSupportedLanguages()
                font.pixelSize: 20
                onCurrentTextChanged: {
                    translate.target = currentText
                    translate.word = sourceWord.item.text
                }
                Layout.fillWidth: true
            }
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }
        Loader {
            id: sourceWord
            sourceComponent: textArea
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Loader {
            id: translatedWord
            sourceComponent: textArea
            onLoaded: {
                item.readOnly = true
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        RoundButton {
            id: translateButton
            text: qsTr("Translate")
            font.pixelSize: 20
            onClicked: {
                translate.word = sourceWord.item.text
            }
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }
        RoundButton {
            text: qsTr("Save in dictionary")
            font.pixelSize: 20
            Layout.minimumWidth: translateGrid.width / 2
            Material.background: "#41cd52"
            onClicked: {
                if (!wordsEditModel.ifExist(sourceWord.item.text)) {
                    wordsEditModel.addWord(sourceWord.item.text, translatedWord.item.text)
                    warningLabel.state = "default"
                } else {
                    warningLabel.state = "AlreadyExist"
                }
                popup.open()
            }
        }
        ComboBox {
            model: VocabulariesQueryModel { }
            textRole: "name"
            font.pixelSize: 20
            Layout.minimumWidth: translateGrid.width / 2
            onCurrentIndexChanged: {
                wordsEditModel.vocabularyfilter = model.getItemId(currentIndex)
            }
        }
        Popup {
            id: popup
            x: parent.width / 3
            y: parent.height / 3
            width: parent.width / 2
            height: parent.height / 4
            modal: true
            focus: true
            background: Rectangle {
                color: "#3faf4d"
                radius: 20
            }
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
            ColumnLayout {
                anchors.fill: parent
                Label {
                    id: warningLabel
                    text: qsTr("Word added")
                    horizontalAlignment: Qt.AlignHCenter
                    font.pixelSize: 30
                    Layout.fillWidth: true
                    states: [
                        State {
                            name: "AlreadyExist"
                            PropertyChanges {
                                target: warningLabel
                                text: qsTr("Word already exist")
                            }
                        }
                    ]
                }
                RoundButton {
                    text: qsTr("Ok")
                    font.pixelSize: 30
                    onClicked: {
                        popup.close()
                    }
                    Layout.alignment: Qt.AlignHCenter
                    Material.background: Material.Red
                }
            }
        }
    }
}
