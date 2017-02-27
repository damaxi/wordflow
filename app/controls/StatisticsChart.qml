import QtQuick 2.5
import QtCharts 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Styles 1.4

ChartView {
    id: chart
    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime();
        return msecs;
    }

    function daysInMonth() {
        var currentDate = new Date()
        var firstDayNextMoth = new Date(currentDate.getFullYear(), currentDate.getMonth() + 1, 1)
        var lastDay = new Date(firstDayNextMoth - 1);
        return lastDay.getDate()
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
    property alias dateAxis: dateLoader.sourceComponent
    property alias allWordsSeries: allWordsAxis.upperSeries
    property alias learnedWordsSeries: learnedWordsAxis.upperSeries
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
            format: "d"
            tickCount: chart.daysInMonth()
            color: "white"
            labelsColor: "white"
            labelsFont { bold: true; pixelSize: 10 }
            shadesVisible: true
            gridVisible: false
        }
    }

    Component {
        id: annualDateAxis
        DateTimeAxis {
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

    AreaSeries {
        id: allWordsAxis
        axisX: dateLoader.item
        axisY: valueAxis
        color: "#41cd52"
        name: qsTr("All worlds")
        upperSeries: LineSeries { }
   }
   AreaSeries {
       id: learnedWordsAxis
       axisX: dateLoader.item
       axisY: valueAxis
       name: qsTr("Newly learned")
       upperSeries: LineSeries { }
   }
}
