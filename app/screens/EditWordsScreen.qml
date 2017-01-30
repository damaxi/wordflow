import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.4

Pane {
    id: editWordsScreen
    focus: true
    property var wordsArray: []
    function reload() {
        wordsArray = vocabularyImpl.listWords(window.current_vocabulary_id)
        list.forceActiveFocus() //this is the hack probably something stole focusing
    }

    Component.onCompleted: {
        reload()
    }
    Component {
        id: wordRow
        RowLayout {
            width: editWordsScreen.width
            Label {
                text: modelData.origin;
                font.pixelSize: 24
                Layout.minimumWidth: editWordsScreen.width * 2 / 6
                elide: Text.ElideRight
                Layout.fillWidth: true
            }
            Label {
                text: modelData.translated;
                font.pixelSize: 24
                Layout.minimumWidth: editWordsScreen.width * 2 / 6
                elide: Text.ElideRight
                Layout.fillWidth: true
            }
            ProgressBar {
                value: modelData.progress
                from: 0; to: 100
                implicitWidth: editWordsScreen.width * 2 / 6
                Layout.minimumWidth: implicitWidth
                Layout.alignment: Qt.AlignCenter
                Material.foreground: Material.Red
            }
        }
    }

    Component {
        id: wordHeader
        RowLayout {
            width: editWordsScreen.width
            Label {
                text: "Word List"
                font { pixelSize: 28; bold: true }
                horizontalAlignment: Qt.AlignHCenter
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
            focus: true
            spacing: 5
            height: editWordsScreen.height
            model: editWordsScreen.wordsArray
            header: wordHeader
            delegate: wordRow
            highlight: highlight
        }
        GridLayout {
            columns: 2; rows: 2

        }
    }
}
