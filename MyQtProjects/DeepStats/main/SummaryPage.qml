import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import QtQuick.Controls 1.4         // Calendar
import QtQuick.Controls.Styles 1.4  // Calendar Style

//import ca.scumpyware.deepstats 1.0
// NOTE this page doesn't know anything about the Portal.
// It just passes stuff back & forth with signals & properties...

//Item {  // Top level container...

Rectangle {  // Top level container...
    color: "black"

    property string numRides:  "0";
    property string totDist:   "0";
    property string avgDist:   "0";
    property string medDist:   "0";
    property string totMTime:  "0";
    property string avgMTime:  "0";
    property string medMTime:  "0";
    property string longRide:  "0";
    property string longMTime: "0";

    property string textOne: "#75FFFF";
    property string textTwo: "#FF8080"

    signal doSummarize(string startDateStr, string endDateStr);

    Item {
        id: dates

        width: startGroupBox.width + endGroupBox.width
        height: startGroupBox.height

        anchors.topMargin: 20
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        RowLayout {
            GroupBox {
                id: startGroupBox
                title: "Select a Start Date"
                ColumnLayout {
                    Calendar {
                        id: startCalandar

                        Component.onCompleted: {
                            startCalandar.selectedDate = new Date (2016,0,1);
                        }

                        style: CalendarStyle {
                            gridVisible: false
                            dayDelegate: Rectangle {
                                gradient: Gradient {
                                    GradientStop {
                                        position: 0.00
                                        color: styleData.selected ? "#111" : (styleData.visibleMonth && styleData.valid ? "#444" : "#666");
                                    }
                                    GradientStop {
                                        position: 1.00
                                        color: styleData.selected ? "#444" : (styleData.visibleMonth && styleData.valid ? "#111" : "#666");
                                    }
                                    GradientStop {
                                        position: 1.00
                                        color: styleData.selected ? "#777" : (styleData.visibleMonth && styleData.valid ? "#111" : "#666");
                                    }
                                }

                                Label {
                                    text: styleData.date.getDate()
                                    anchors.centerIn: parent
                                    color: styleData.valid ? "white" : "grey"
                                }

                                Rectangle {
                                    width: parent.width
                                    height: 1
                                    color: "#555"
                                    anchors.bottom: parent.bottom
                                }

                                Rectangle {
                                    width: 1
                                    height: parent.height
                                    color: "#555"
                                    anchors.right: parent.right
                                }
                            }
                        }
                    }

                    Label {
                        id: startDateLabel
                        text: startCalandar.selectedDate.toLocaleString(Qt.locale(),"yyyy-MMM-dd");
                        font.pixelSize: 22
                        font.italic: true
                        font.bold: true
                        color: textOne
                    }
                }
            }

            GroupBox {
                id: endGroupBox
                title: "Select a End Date"
                ColumnLayout {
                    Calendar {
                        id: endCalandar

                        Component.onCompleted: {
                            endCalandar.selectedDate = new Date (); // Current Date
                        }

                        style: CalendarStyle {
                            gridVisible: false
                            dayDelegate: Rectangle {
                                gradient: Gradient {
                                    GradientStop {
                                        position: 0.00
                                        color: styleData.selected ? "#111" : (styleData.visibleMonth && styleData.valid ? "#444" : "#666");
                                    }
                                    GradientStop {
                                        position: 1.00
                                        color: styleData.selected ? "#444" : (styleData.visibleMonth && styleData.valid ? "#111" : "#666");
                                    }
                                    GradientStop {
                                        position: 1.00
                                        color: styleData.selected ? "#777" : (styleData.visibleMonth && styleData.valid ? "#111" : "#666");
                                    }
                                }

                                Label {
                                    text: styleData.date.getDate()
                                    anchors.centerIn: parent
                                    color: styleData.valid ? "white" : "grey"
                                }

                                Rectangle {
                                    width: parent.width
                                    height: 1
                                    color: "#555"
                                    anchors.bottom: parent.bottom
                                }

                                Rectangle {
                                    width: 1
                                    height: parent.height
                                    color: "#555"
                                    anchors.right: parent.right
                                }
                            }
                        }
                    }

                    Label {
                        id: endDateLabel
                        text: endCalandar.selectedDate.toLocaleString(Qt.locale(),"yyyy-MMM-dd");
                        font.pixelSize: 22
                        font.italic: true
                        font.bold: true
                        color: textOne
                    }
                }
            }
        }
    }

    Rectangle {
        id: summarizeButton
        width: dates.width
        height: 40
        anchors.top: dates.bottom;
        anchors.topMargin: 20;
        anchors.horizontalCenter: parent.horizontalCenter;

        border.width: 2
        border.color: "white"
        radius: 20

        gradient: Gradient {
//                GradientStop { position: 0.0; color: "lightsteelblue" }
//                GradientStop { position: 1.0; color: "blue" }
            GradientStop { position: 0.0; color: "lightgrey" }
            GradientStop { position: 1.0; color: "black" }
            }

        Text {
            text: "Summarize!";
            font.pixelSize: 30;
            font.italic: true;
            font.bold: true;
            color: textOne;
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                print("Summarize button clicked: Summarize from:");
    //            print(startDateLabel.text + " TO ");
    //            print(endDateLabel.text);

                // Signal out that we want to do a summary...
                doSummarize(startDateLabel.text, endDateLabel.text);
            }
        }
    }

    GroupBox {
        id: summaryGroupBox

        anchors.top: summarizeButton.bottom;
        anchors.topMargin: 20;
        anchors.horizontalCenter: parent.horizontalCenter;

        ColumnLayout {
            RowLayout {
                Label {
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 2)
                    text: "Number of Rides:";
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textOne;
                }
                Label {
                    id: numRidesLabel
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 1)
                    text: numRides;
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textTwo;
                }
            }

            RowLayout {
                Label {
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 2)
                    text: "Total Dist (Kms):";
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textOne;
                }
                Label {
                    id: totDistLabel
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 1)
                    text: totDist;
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textTwo;
                }
            }

            RowLayout {
                Label {
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 2)
                    text: "Average Dist (Kms):";
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textOne;
                }
                Label {
                    id: avgDistLabel
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 1)
                    text: avgDist;
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textTwo;
                }
            }

            RowLayout {
                Label {
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 2)
                    text: "Median Dist (Kms):";
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textOne;
                }
                Label {
                    id: medDistLabel
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 1)
                    text: medDist;
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textTwo;
                }
            }

            RowLayout {
                Label {
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 2)
                    text: "Total Moving Time:";
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textOne;
                }
                Label {
                    id: totMTimeLabel
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 1)
                    text: totMTime;
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textTwo;
                }
            }

            RowLayout {
                Label {
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 2)
                    text: "Average Moving Time:";
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textOne;
                }
                Label {
                    id: avgMTimeLabel
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 1)
                    text: avgMTime;
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textTwo;
                }
            }

            RowLayout {
                Label {
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 2)
                    text: "Median Moving Time:";
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textOne;
                }
                Label {
                    id: medMTimeLabel
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 1)
                    text: medMTime;
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textTwo;
                }
            }

            RowLayout {
                Label {
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 2)
                    text: "Longest Ride (Kms):";
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textOne;
                }
                Label {
                    id: longRideLabel
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 1)
                    text: longRide;
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textTwo;
                }
            }

            RowLayout {
                Label {
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 2)
                    text: "Longest Moving Time:";
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textOne;
                }
                Label {
                    id: longMTimeLabel
                    Layout.preferredWidth: ((summarizeButton.width / 3) * 1)
                    text: longMTime;
                    font.pixelSize: 30;
                    font.italic: true;
                    font.bold: true;
                    color: textTwo;
                }
            }
        }
    }
}
