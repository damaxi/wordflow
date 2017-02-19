import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0
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

        Screen.EditVocabulariesScreen {
            id: vocabularyScreen
        }

        Connections {
            target: vocabularyScreen.confirmationButton
            onClicked: {
                if (vocabularyScreen.vocabularyInputText.length > 0
                        && vocabularyScreen.descriptionInputText.length > 0) {
                    vocabularyImpl.createVocabulary(
                                vocabularyScreen.vocabularyInputText,
                                vocabularyScreen.descriptionInputText)
                    configurationPopup.close()
                } else {
                    vocabularyScreen.popup.text = qsTr("One of input is empty!")
                    vocabularyScreen.popup.visible = true
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
