import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4
import io.github.damaxi 1.0
import "../controls" as Controls

Pane {
    id: editVocabularyScreen
    focus: true

    Component {
        id: vocabularyRow
        Column {
            id: delegateRow
            property alias vocabulary: vocabularyLabel.text
            property alias description: descriptionLabel.text
            width: editVocabularyScreen.width
            spacing: 5
            Label {
                id: vocabularyLabel
                text: model.name
                anchors.left: delegateRow.left
                anchors.right: delegateRow.right
                horizontalAlignment: Qt.AlignHCenter
                font { pixelSize: 24; bold: true }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        list.currentIndex = index
                    }
                }
            }
            Label {
                id: descriptionLabel
                text: model.description
                anchors.left: delegateRow.left
                anchors.right: delegateRow.right
                horizontalAlignment: Qt.AlignHCenter
                font.pixelSize: 24
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        list.currentIndex = index
                    }
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        ListView {
            id: list
            Layout.fillHeight: true
            focus: true
            spacing: 15
            model: VocabulariesEditModel { }
            delegate: vocabularyRow
            highlight: Controls.HighlightComponent { }
            onCurrentItemChanged: {
                vocabularyArea.setText(currentItem.vocabulary)
                descriptionArea.text = currentItem.description
            }
        }

        GridLayout {
            id: contextPanel
            property int buttonWidth: editVocabularyScreen.width / 3
            Keys.onPressed: {
                if (event.key == Qt.Key_Down || event.key == Qt.Key_Up) {
                    list.forceActiveFocus()
                }
            }
            Layout.fillWidth: true
            columns: 3; rows: 4;
            RoundButton {
                text: qsTr("Clear")
                Layout.columnSpan: 3
                Layout.fillWidth: true
                Material.background: "#3faf4d"
                onClicked: {
                    vocabularyArea.clear()
                    descriptionArea.clear()
                }
            }
            Label {
                text: qsTr("Vocabulary: ")
                font.pixelSize: 20
            }
            ComboBox {
                id: vocabularyArea
                function setText(text)
                {
                    var index = find(text);
                    if (index != -1) currentIndex = index
                }
                property alias text: vocabularyArea.currentText
                model: LocaleModel { }
                textRole: "display"
                Layout.fillWidth: true
                Layout.columnSpan: 2
                KeyNavigation.priority: KeyNavigation.BeforeItem
                KeyNavigation.tab: descriptionArea
            }
            Label {
                text: qsTr("Description: ")
                font.pixelSize: 20
            }
            TextArea {
                id: descriptionArea
                text: ""
                Layout.fillWidth: true
                Layout.columnSpan: 2
                KeyNavigation.priority: KeyNavigation.BeforeItem
                KeyNavigation.tab: vocabularyArea
            }
            RoundButton {
                text: qsTr("Update")
                Layout.preferredWidth: contextPanel.buttonWidth
                Layout.fillWidth: true
                onClicked: {
                    list.model.updateVocabulary(list.currentIndex, vocabularyArea.text, descriptionArea.text)
                    vocabularyBox.reload()
                }
            }
            RoundButton {
                text: qsTr("Add")
                Layout.preferredWidth: contextPanel.buttonWidth
                Layout.fillWidth: true
                onClicked: {
                    list.model.addVocabulary(vocabularyArea.text, descriptionArea.text)
                    vocabularyBox.reload()
                }
            }
            RoundButton {
                text: qsTr("Delete")
                Layout.preferredWidth: contextPanel.buttonWidth
                Layout.fillWidth: true
                onClicked: {
                    list.model.deleteVocabulary(list.currentIndex)
                    vocabularyBox.reload()
                }
            }
        }
    }
}
