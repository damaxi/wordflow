import QtQuick 2.5
import QtCharts 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Styles 1.4
import "../controls" as Controls

Pane {
    id: statisticScreen
    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime();
        return msecs;
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 20
            spacing: 20
            Label {
                text: "Total: 20"
                font { bold: true; pixelSize: 20 }
                Layout.fillWidth: true
            }
            Label {
                text: "Learned: 20"
                font { bold: true; pixelSize: 20 }
                Layout.fillWidth: true
            }
            Label {
                text: "Average: 20"
                font { bold: true; pixelSize: 20 }
                Layout.fillWidth: true
            }
        }

        Controls.StatisticsChart {
            id: statisticChart
//                allWords: LineSeries {
//                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 1)); y: 5 }
//                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 2)); y: 50 }
//                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 3)); y: 102 }
//                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 4)); y: 100 }
//                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 5)); y: 110 }
//                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 6)); y: 110 }
//                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 7)); y: 110 }
//                }
//                learnedWords: LineSeries {
//                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 1)); y: 1 }
//                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 2)); y: 40 }
//                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 3)); y: 50 }
//                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 4)); y: 50 }
//                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 5)); y: 60 }
//                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 6)); y: 60 }
//                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 7)); y: 110 }
//                }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        TabBar{
            id: bar
            Layout.fillWidth: true
            TabButton {
                text: qsTr("Weekly")
                onClicked: {
                    statisticChart.changeDateAxis("week")
                }
            }
            TabButton {
                text: qsTr("Monthly")
                onClicked: {
                   statisticChart.changeDateAxis("monthly")
                }
            }
            TabButton {
                text: qsTr("Annul")
                onClicked: {
                    statisticChart.changeDateAxis("annual")
                }
            }
        }
    }
}
