import QtQuick 2.5
import QtCharts 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Styles 1.4

Pane {
    id: statisticScreen

    Component {
        id: weekly

        ChartView {
            function toMsecsSinceEpoch(date) {
                var msecs = date.getTime();
                return msecs;
            }
            antialiasing: true
            backgroundColor: "transparent"
            backgroundRoundness: 0
            legend {
                alignment: Qt.AlignBottom;
                font { bold: true; pixelSize: 15; }
                labelColor: "white"
            }

            DateTimeAxis {
                id: weekDateAxis
                format: "ddd"
                tickCount: 7
                color: "white"
                labelsColor: "white"
                labelsAngle: 45
                labelsFont.bold: true
                shadesVisible: true
            }

            ValueAxis {
                id: valueAxis
                min: 0
                max: 150
                color: "white"
                labelsColor: "white"
            }

            AreaSeries {
                axisX: weekDateAxis
                axisY: valueAxis
                color: "#41cd52"
                name: "All worlds"
                upperSeries:  LineSeries {
                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 1)); y: 5 }
                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 2)); y: 50 }
                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 3)); y: 102 }
                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 4)); y: 100 }
                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 5)); y: 110 }
                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 6)); y: 110 }
                    XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 7)); y: 110 }
                }
           }
           AreaSeries {
               axisX: weekDateAxis
               axisY: valueAxis
               name: "Newly learned"
               upperSeries: LineSeries {
                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 1)); y: 1 }
                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 2)); y: 40 }
                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 3)); y: 50 }
                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 4)); y: 50 }
                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 5)); y: 60 }
                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 6)); y: 60 }
                   XYPoint { x: toMsecsSinceEpoch(new Date(2017, 2, 7)); y: 110 }
               }
           }
        }
    }

    Component {
        id: monthly
        ChartView {
            antialiasing: true

            LineSeries {
                name: "LineSeries"
                XYPoint { x: 0; y: 0 }
                XYPoint { x: 1.1; y: 2.1 }
                XYPoint { x: 3.4; y: 3.0 }
                XYPoint { x: 4.1; y: 3.3 }
            }
        }
    }

    Component {
        id: annual
        ChartView {
            antialiasing: true

            LineSeries {
                name: "LineSeries"
                XYPoint { x: 0; y: 0 }
                XYPoint { x: 1.1; y: 2.1 }
                XYPoint { x: 2.9; y: 4.9 }
                XYPoint { x: 3.4; y: 3.0 }
                XYPoint { x: 4.1; y: 3.3 }
            }
        }
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

        StackView {
            id: statisticStack
            initialItem: weekly
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        TabBar{
            id: bar
            Layout.fillWidth: true
            TabButton {
                text: qsTr("Weekly")
                onClicked: {
                    statisticStack.replace(weekly)
                }
            }
            TabButton {
                text: qsTr("Monthly")
                onClicked: {
                    statisticStack.replace(monthly)
                }
            }
            TabButton {
                text: qsTr("Annul")
                onClicked: {
                    statisticStack.replace(annual)
                }
            }
        }
    }
}
