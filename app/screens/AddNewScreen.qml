import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4

Pane {
    ColumnLayout {
        id: addWordScreen

        spacing: 2
        anchors.fill: parent
        focus: true

        Label {
            font.pixelSize: 20
            text: qsTr("Native: ")
        }

        TextArea {
            id: origin
            Layout.fillWidth: true
            wrapMode: TextEdit.Wrap
            KeyNavigation.tab: translated
            KeyNavigation.priority: KeyNavigation.BeforeItem
        }

        Label {
            font.pixelSize: 20
            text: qsTr("Foreign: ")
        }

        TextArea {
            id: translated
            Layout.fillWidth: true
            wrapMode: TextEdit.Wrap
            KeyNavigation.tab: add
            KeyNavigation.priority: KeyNavigation.BeforeItem
        }

        Button {
            id: add
            text: qsTr("Add")
            Layout.columnSpan: 2
            Layout.fillWidth: true
            focus: true
            KeyNavigation.tab: origin
            Keys.onReturnPressed: clicked()
            onClicked: {
                var current_vocabulary_id = window.vocabularyList[vocabularyBox.currentIndex].id
                var result = vocabularyImpl.createWord(origin.text, translated.text, current_vocabulary_id)
                if (result) {
                    popup.state = "success"
                } else {
                    popup.state = "alert"
                }
            }
        }

        Label {
            id: popup
            font.pixelSize: 20
            visible: false
            horizontalAlignment: Label.AlignHCenter
            Layout.fillWidth: true
            states: [
                State {
                    name: "alert"
                    PropertyChanges {
                        target: popup
                        text: qsTr("Fail. Already exist in database.")
                        visible: true
                        Material.foreground: Material.Red
                    }
                },
                State {
                    name: "success"
                    PropertyChanges {
                        target: popup
                        text: qsTr("Success")
                        visible: true
                        Material.foreground: Material.Green
                    }
                }
            ]
        }
    }
}
