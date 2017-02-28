import QtQuick 2.5
import QtCharts 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Styles 1.4
import io.github.damaxi 1.0

ChartView {
    id: chart
    function updateAllWordsSeries()
    {
        var existingSeries = chart.series(qsTr("All worlds"));
        if (existingSeries != null) chart.removeSeries(existingSeries);
        var areaSeries = chart.createSeries(ChartView.SeriesTypeArea, qsTr("All worlds"),
                dateLoader.item, valueAxis)
        areaSeries.color = "#41cd52"
        return areaSeries.upperSeries
    }

    function updateLearnedWordsSeries()
    {
        var existingSeries = chart.series(qsTr("Newly learned"));
        if (existingSeries != null) chart.removeSeries(existingSeries);
        var areaSeries = chart.createSeries(ChartView.SeriesTypeArea, qsTr("Newly learned"),
                dateLoader.item, valueAxis)
        return areaSeries.upperSeries
    }

    function changeDateAxis(datePeriod) {
        switch(datePeriod) {
            case "week":
                dateAxis = weekDateAxis
            break;
            case "monthly":
                dateAxis = monthDateAxis
            break;
            case "annual":
                dateAxis = annualDateAxis
            break;
        }
    }

    DateHelper {
        id: dateHelper
    }

    property alias dateAxis: dateLoader.sourceComponent
    property alias  maximumValue: valueAxis.max
    antialiasing: true
    backgroundColor: "transparent"
    backgroundRoundness: 0
    legend {
        alignment: Qt.AlignBottom;
        font { bold: true; pixelSize: 15; }
        labelColor: "white"
    }

    Component {
        id: weekDateAxis
        DateTimeAxis {
            format: "ddd"
            max: dateHelper.getCurrentDate()
            min: dateHelper.getWeekAgoDate()
            tickCount: 7
            color: "white"
            labelsColor: "white"
            labelsAngle: 45
            labelsFont.bold: true
            shadesVisible: true
            gridVisible: false
        }
    }

    Component {
        id: monthDateAxis
        DateTimeAxis {
            max: dateHelper.getCurrentDate()
            min: dateHelper.getMonthAgoDate()
            format: "d"
            tickCount: dateHelper.getDaysInCurrentMonth()
            color: "white"
            labelsColor: "white"
            labelsFont { bold: true; pixelSize: 8 }
            shadesVisible: true
            gridVisible: false
        }
    }

    Component {
        id: annualDateAxis
        DateTimeAxis {
            max: dateHelper.getCurrentDate()
            min: dateHelper.getYearAgoDate()
            format: "MMM"
            tickCount: 12
            color: "white"
            labelsColor: "white"
            labelsAngle: 45
            labelsFont { bold: true; pixelSize: 10 }
            shadesVisible: true
            gridVisible: false
        }
    }

    Loader {
        id: dateLoader
        sourceComponent: weekDateAxis
    }

    ValueAxis {
        id: valueAxis
        min: 0
        max: 150
        color: "white"
        labelsColor: "white"
    }
}
