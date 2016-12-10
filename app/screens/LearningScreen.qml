import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4

Pane {
    id: learnScreen
    property var wordArray: []
    property int index: 0

    function setNewWord() {
        origin.item.text = wordArray[index][0];
        translated.item.hiddenText = wordArray[index][1];
    }

    function setPrevious() {
        if (index == 0) {
            index = wordArray.length - 1;
        } else {
            index -= 1;
        }

        setNewWord();
    }

    function setNext() {
        if (index == wordArray.length - 1) {
            index = 0;
        } else {
            index += 1;
        }

        setNewWord();
    }

    function getWord(id) {
        var obj;
        var database = window.db();
        database.transaction(
            function(tx) {
                var result = tx.executeSql('SELECT origin, translated FROM words WHERE id = ?', [id]);
                obj = { origin:result.rows.item(0).origin, translated:result.rows.item(0).translated };
            }
        )
        return obj;
    }

    function loadFirstNWords(n) {
        var database = window.db();
        database.transaction(
            function(tx) {
                var result = tx.executeSql('SELECT origin, translated FROM words LIMIT ?', [n]);
                for (var i = 0; i < result.rows.length; i++) {
                    learnScreen.wordArray.push([result.rows.item(i).origin, result.rows.item(i).translated]);
                }
            }
        )
    }

    Component {
        id: hoveringButton

        Button {
            id: button
            property string hiddenText: ''
            font.pixelSize: 24
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
                        font.pixelSize: 28
                    }
                }
            ]
        }
    }

    ColumnLayout {

        Component.onCompleted: {
            learnScreen.loadFirstNWords(5);
            if (wordArray.length != 0) learnScreen.setNewWord();
        }

        anchors.fill: parent
        spacing: 0

        Label {
            visible: wordArray.length ? false : true
            text: qsTr('Your dictonary is empty.')
            font.pixelSize: 24
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        Loader {
            id: origin
            visible: wordArray.length ? true : false
            sourceComponent: hoveringButton
            Material.background: Material.DeepPurple
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Loader {
            id: translated
            visible: wordArray.length ? true : false
            sourceComponent: hoveringButton
            Material.background: Material.DeepOrange
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        RowLayout {
            id: nextprevLayout
            spacing: 20
            visible: wordArray.length ? true : false

            Button {
                text: qsTr("Previous")
                Layout.minimumWidth: parent.width / 2 - nextprevLayout.spacing
                Layout.fillWidth: true
                onClicked: learnScreen.setPrevious()
            }

            Button {
                text: qsTr("Next")
                Layout.minimumWidth: parent.width / 2 - nextprevLayout.spacing
                Layout.fillWidth: true
                onClicked: learnScreen.setPrevious()
            }
        }
    }
}
