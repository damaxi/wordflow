import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4

Pane {
    ColumnLayout {
        id: addWordScreen
        function addWord(origin, translated) {
            var database = window.db();
            database.transaction(
                function(tx) {
                    var inserted_id = tx.executeSql('INSERT INTO words (vocabulary, origin, translated) VALUES(?, ?, ?)',
                                  [0, origin, translated]);
                    // console.log(inserted_id.insertId);
                }
            )
        }

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
            KeyNavigation.tab: origin
            KeyNavigation.priority: KeyNavigation.BeforeItem
        }

        Button {
            id: add
            text: qsTr("Add")
            Layout.columnSpan: 2
            Layout.fillWidth: true
            focus: true
            Keys.onEnterPressed: console.log("hej")
            onClicked: {
                try {
                    addWordScreen.addWord(origin.text, translated.text)
                    popup.state = "success"
                } catch (e) {
                    console.log(e);
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
