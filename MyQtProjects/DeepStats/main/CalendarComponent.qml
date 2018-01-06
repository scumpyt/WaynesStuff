import QtQuick 2.0

import QtQuick.Controls 1.4         // Calendar
import QtQuick.Controls.Styles 1.4  // Calendar Style

Item {
    id: root

    property alias promptText: prompt.text;
    property alias promptFont: prompt.font.family;
    property alias promptPixelSize: prompt.font.pixelSize;
    property alias promptColor: prompt.color;

    // Add default/initial date...

    signal dateSelected;

    // Local properties...
    property int originalHeight: 0

    Component.onCompleted: {
        originalHeight = root.height;   // One time assignment... No binding, right???
    }

    states: [
        State {
            name: "shown"
            PropertyChanges { target: theCal; visible: true }
            //PropertyChanges { target: root; height: calRect1.height + theCal.height }
            PropertyChanges { target: root;
                              height: Math.min((originalHeight+theCal.height), (calRect1.height + theCal.height))
                            }
        },
        State {
            name: "hidden"
            PropertyChanges { target: theCal; visible: false }
            //PropertyChanges { target: root; height: calRect1.height }
            PropertyChanges { target: root; height: originalHeight }
        }
    ]

    Rectangle {
        id: calRect1

        anchors.top: root.top
        width:  Math.max(theCal.width, prompt.width);
        height: prompt.height * 1.1

        color: "transparent"
        border.color: prompt.color
        border.width: 2
        radius: 15
        Text {
            id: prompt
            text: "Enter Date"
            font.family: "Ubuntu"
            font.pixelSize: 20
            font.italic: true
            font.bold: true
            color: "red"
            anchors.centerIn: parent

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    //root.clicked()
                    print("TEXT selected!");
                    root.state = "shown"
                }
            }
        }
    }

    Calendar {
        id: theCal
        anchors.top: calRect1.bottom

        visible: false

        Component.onCompleted: {
            theCal.selectedDate = new Date (2016,0,1);
        }

        onClicked: {
            print("DATE Clicked!");
            promptText = theCal.selectedDate.toLocaleString(Qt.locale(),"yyyy-MMM-dd")
            root.state = "hidden"
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
}
