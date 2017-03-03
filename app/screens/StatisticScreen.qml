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
    function loadStatistics(type) {
        chartModel.type = type;
        switch(type) {
            case StatisticChartModel.WEEKLY:
                statisticChart.changeDateAxis("week")
                chartModel.setAllWeekSeries(statisticChart.updateAllWordsSeries())
                chartModel.setLearnedWeekSeries(statisticChart.updateLearnedWordsSeries())
            break;
            case StatisticChartModel.MONTHLY:
                statisticChart.changeDateAxis("monthly")
                chartModel.setAllMonthSeries(statisticChart.updateAllWordsSeries())
                chartModel.setLearnedMonthSeries(statisticChart.updateLearnedWordsSeries())
            break;
            case StatisticChartModel.ANNUAL:
                statisticChart.changeDateAxis("annual")
                chartModel.setAllYearSeries(statisticChart.updateAllWordsSeries())
                chartModel.setLearnedYearSeries(statisticChart.updateLearnedWordsSeries())
            break;
        }
    }

    StatisticChartModel {
        id: chartModel
        property int type: StatisticChartModel.WEEKLY
        vocabulary: window.current_vocabulary_id
        onVocabularyChanged: {
            loadStatistics(type)
        }
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            spacing: 20
            Label {
                text: "Total: %1".arg(chartModel.total)
                font { bold: true; pixelSize: 20 }
                horizontalAlignment: Qt.AlignRight
                Layout.fillWidth: true
            }
            Label {
                text: "Learned: %1".arg(chartModel.learned)
                font { bold: true; pixelSize: 20 }
                horizontalAlignment: Qt.AlignHCenter
                Layout.fillWidth: true
            }
            Label {
                text: "Average: %1".arg(chartModel.average)
                font { bold: true; pixelSize: 20 }
                horizontalAlignment: Qt.AlignLeft
                Layout.fillWidth: true
            }
        }

        Controls.StatisticsChart {
            id: statisticChart
            Layout.fillWidth: true
            Layout.fillHeight: true
            maximumValue: chartModel.maxValue
            Component.onCompleted: {
                loadStatistics(StatisticChartModel.WEEKLY)
            }
        }

        TabBar{
            id: bar
            Layout.fillWidth: true
            TabButton {
                id: weekly
                text: qsTr("Weekly")
                onClicked: {
                    loadStatistics(StatisticChartModel.WEEKLY)
                }
            }
            TabButton {
                id: monthly
                text: qsTr("Monthly")
                onClicked: {
                    loadStatistics(StatisticChartModel.MONTHLY)
                }
            }
            TabButton {
                id: annual
                text: qsTr("Annual")
                onClicked: {
                    loadStatistics(StatisticChartModel.ANNUAL)
                }
            }
        }
    }
}
