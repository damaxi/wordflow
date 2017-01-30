import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4

Pane {
    focus: true
    property alias confirmationButton: confirmNewVocabularyButton
    property alias vocabularyInputText: vocabularyInput.text
    property alias descriptionInputText: descriptionInput.text
    property alias popup: popup

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
                validator: RegExpValidator { regExp: /^[A-Z].*/ }
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

        Label {
            id: confirmPopup
            font.pixelSize: 20
            font.bold: true
            visible: false
            horizontalAlignment: Label.AlignHCenter
            Layout.fillWidth: true
            Material.foreground: Material.Green
        }

        Button {
            id: confirmNewVocabularyButton
            function checkDenyPopup() {
                if (confirmPopup.visible) confirmPopup.visible = false
                popup.visible = true
            }
            function checkConfirmPopup() {
                if (popup.visible) popup.visible = false
                confirmPopup.visible = true
            }
            text: "Add"
            Layout.fillWidth: true
            Keys.onReturnPressed: clicked()
            KeyNavigation.tab: vocabularyInput
            onClicked: {
                if (vocabularyInput.text.length > 0
                        && descriptionInput.text.length > 0) {
                    var ifAlreadyExist = vocabularyImpl.createVocabulary(
                                vocabularyInput.text,
                                descriptionInput.text)
                    if (ifAlreadyExist) {
                        window.vocabularyList = vocabularyImpl.listVocabularies()
                        confirmPopup.text = qsTr("Vocabulary Added.")
                        checkConfirmPopup()
                    } else {
                        popup.text = qsTr("Record Already Exist!")
                        checkDenyPopup()
                    }
                } else {
                    popup.text = qsTr("One of input is empty!")
                    checkDenyPopup()
                }
            }
        }
    }
}
