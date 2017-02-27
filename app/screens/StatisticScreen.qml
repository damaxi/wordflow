import QtQuick 2.5
import QtCharts 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Styles 1.4
import io.github.damaxi 1.0
import "../controls" as Controls

Pane {
    id: statisticScreen

    StatisticChartModel {
        id: chartModel
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
            Layout.fillWidth: true
            Layout.fillHeight: true
            Component.onCompleted: {
                chartModel.setWeekSeries(statisticChart.allWordsSeries)
                console.log(statisticChart.allWordsSeries.count)
                statisticChart.update()
            }
        }

        TabBar{
            id: bar
            Layout.fillWidth: true
            TabButton {
                text: qsTr("Weekly")
                onClicked: {
                    statisticChart.changeDateAxis("week")
                    //chartModel.setWeekSeries(statisticChart.allWordsSeries)
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
