import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0

Popup {
    id: configurationPopup
    closePolicy: Popup.NoAutoClose
    width: window.width
    height: window.height
    focus: true

    SwipeView {
        id: introView
        currentIndex: 0
        anchors.fill: parent
        anchors.bottomMargin: 50
        focus: true

        Item {
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

        Item {
            focus: true

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20

                Label {
                    font.pixelSize: 25
                    font.bold: true
                    text: qsTr("Add vocabulary to start")
                    horizontalAlignment: Qt.AlignHCenter
                    Layout.fillWidth: true
                }

                RowLayout {

                    Label {
                        font.pixelSize: 20
                        text: qsTr("Vocabulary: ")
                    }

                    TextField {
                        id: vocabularyInput
                        maximumLength: 25
                        Layout.fillWidth: true
                        KeyNavigation.tab: descriptionInput
                    }
                }

                RowLayout {

                    Label {
                        font.pixelSize: 20
                        text: qsTr("Description: ")
                    }

                    TextField {
                        id: descriptionInput
                        maximumLength: 25
                        Layout.fillWidth: true
                        KeyNavigation.tab: confirmNewVocabularyButton
                    }
                }

                Label {
                    id: popup
                    font.pixelSize: 20
                    font.bold: true
                    visible: false
                    horizontalAlignment: Label.AlignHCenter
                    Layout.fillWidth: true
                    Material.foreground: Material.Red
                }

                Button {
                    id: confirmNewVocabularyButton
                    text: "Add"
                    Layout.fillWidth: true
                    Keys.onReturnPressed: clicked()
                    KeyNavigation.tab: vocabularyInput
                    onClicked: {
                        if (vocabularyInput.text.length > 0
                                && descriptionInput.text.length > 0) {
                            vocabularyImpl.createVocabulary(
                                        vocabularyInput.text,
                                        descriptionInput.text)
                            configurationPopup.close()
                        } else {
                            popup.text = qsTr("One of input is empty!")
                            popup.visible = true
                        }
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
