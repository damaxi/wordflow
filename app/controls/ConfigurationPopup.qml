import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0
import io.github.damaxi 1.0
import "../screens" as Screen

Popup {
    id: configurationPopup
    closePolicy: Popup.NoAutoClose
    width: window.width
    height: window.height
    focus: true
    padding: 0

    SwipeView {
        id: introView
        currentIndex: 0
        anchors.fill: parent
        anchors.bottomMargin: 50
        focus: true

        Pane {
            id: aboutPage

            ColumnLayout {
                anchors.fill: parent

                Label {
                    id: welcomeLabel
                    text: qsTr("Welcome to wordflow!")
                    font.pixelSize: 25
                    font.bold: true
                    horizontalAlignment: Label.AlignHCenter
                    verticalAlignment: Label.AlignVCenter
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    MouseArea {
                        anchors.fill: parent
                        onClicked: introView.currentIndex++
                    }
                }
            }
        }

        Pane {
            id: vocabularyScreen

            GridLayout {
                anchors.fill: parent
                anchors.margins: 50
                columns: 2; rows: 4

                VocabulariesEditModel {
                    id: model
                }

                Label {
                    text: qsTr("Initialize Vocabulary")
                    font { pixelSize: 30; bold: true }
                    Layout.columnSpan: 2
                    Layout.alignment: Qt.AlignHCenter
                }
                Label {
                    text: qsTr("Vocabulary: ")
                    font.pixelSize: 20
                    Layout.rightMargin: 30
                }
                ComboBox {
                    id: vocabularyArea
                    property alias text: vocabularyArea.currentText
                    model: LocaleModel { }
                    textRole: "display"
                    Layout.fillWidth: true
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
                    KeyNavigation.priority: KeyNavigation.BeforeItem
                    KeyNavigation.tab: vocabularyArea
                }
                RoundButton {
                    text: qsTr("Add")
                    Layout.preferredWidth: contextPanel.buttonWidth
                    Layout.fillWidth: true
                    Layout.columnSpan: 2
                    onClicked: {
                        model.addVocabulary(vocabularyArea.text, descriptionArea.text)
                        configurationPopup.close()
                    }
                }
            }
        }
    }
    PageIndicator {
        id: indicator

        count: introView.count
        currentIndex: introView.currentIndex

        anchors {
            bottom: introView.bottom
            horizontalCenter: parent.horizontalCenter
        }
    }
}
