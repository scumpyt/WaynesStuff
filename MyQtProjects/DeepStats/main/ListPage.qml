import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

//Item {
Rectangle {
    color: "black"

    // Hook to pass the model in...
    property variant listPageModel

    signal doSort(string sortFieldStr);

    GroupBox {
        id: activitiesGroupBox
        title: "My Ride List"
        width: parent.width-20;
        height: parent.height-20;
        anchors.centerIn: parent

        ListView {
            id: activitiesList
            anchors.fill: parent

            anchors.margins: 10
            delegate: activitiesDelegate
            clip: true

            model: listPageModel

            highlightFollowsCurrentItem: true

            header: listViewHeader
            headerPositioning: ListView.InlineHeader    // Default
            //headerPositioning: ListView.OverlayHeader
            //headerPositioning: ListView.PullBackHeader

            footer: listViewHeader
        }

        Component {
            id: listViewHeader
            Rectangle {
                width: activitiesList.width
                height: 25
                color: "lightblue"

                property int colWidth: 125;

                property string selectedColor: "green"
                property string unSelectedColor: "red"

                function updateHeader (btnText) {
                    print("UPDATE HEADER CALLED WITH " + btnText);

                    if (btnText === "Ride")
                    {
                        indxText.color = selectedColor;
                        indxText.text = "Ride*";
                        doSort(btnText);
                    }
                    else
                    {
                        indxText.color = unSelectedColor;
                        indxText.text = "Ride";
                    }

                    if (btnText === "Date")
                    {
                        dateText.color = selectedColor;
                        dateText.text = "Date*";
                        doSort(btnText);
                    }
                    else
                    {
                        dateText.color = unSelectedColor;
                        dateText.text = "Date";
                    }

                    if (btnText === "Distance")
                    {
                        distInKmsText.color = selectedColor;
                        distInKmsText.text = "Distance*";
                        doSort(btnText);
                    }
                    else
                    {
                        distInKmsText.color = unSelectedColor;
                        distInKmsText.text = "Distance";
                    }

                    if (btnText === "Moving Time")
                    {
                        mTimeText.color = selectedColor;
                        mTimeText.text = "Moving Time*";
                        doSort(btnText);
                    }
                    else
                    {
                        mTimeText.color = unSelectedColor;
                        mTimeText.text = "Moving Time";
                    }

                    if (btnText === "Average Spd")
                    {
                        avgSpdText.color = selectedColor;
                        avgSpdText.text = "Average Spd*";
                        doSort(btnText);
                    }
                    else
                    {
                        avgSpdText.color = unSelectedColor;
                        avgSpdText.text = "Average Spd";
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    spacing: 10
                    Text {
                        id: indxText
                        text: "Ride"
                        color: unSelectedColor
                        font.pointSize: 14
                        Layout.preferredWidth: colWidth
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                updateHeader(indxText.text);
                            }
                        }
                    }
                    Text {
                        id: dateText
                        text: "Date"
                        color: unSelectedColor
                        font.pointSize: 14
                        Layout.preferredWidth: colWidth
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                updateHeader(dateText.text);
                            }
                        }
                    }
                    Text {
                        id: distInKmsText
                        text: "Distance"
                        color: unSelectedColor
                        font.pointSize: 14
                        Layout.preferredWidth: colWidth
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                updateHeader(distInKmsText.text);
                            }
                        }
                    }
                    Text {
                        id: mTimeText
                        text: "Moving Time"
                        color: unSelectedColor
                        font.pointSize: 14
                        Layout.preferredWidth: colWidth
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                updateHeader(mTimeText.text);
                            }
                        }
                    }
                    Text {
                        id: avgSpdText
                        text: "Average Spd"
                        color: unSelectedColor
                        font.pointSize: 14
                        Layout.preferredWidth: colWidth
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                updateHeader(avgSpdText.text);
                            }
                        }
                    }
                }
            }
        }

        Component {
            id: activitiesDelegate
            Rectangle {
                width: activitiesList.width
                height: 25

                // Alternate colors on rows...
//                color: (rideNumber % 2) ? "lightgrey" : "transparent"
                color: (rideNumber % 2) ? "lightgrey" : "darkgrey"

                property int colWidth: 125;

                RowLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    spacing: 10
                    Text {
                        id: indxText
                        text: rideNumber
                        color: "blue"
                        font.pointSize: 14
                        Layout.preferredWidth: colWidth
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                    Text {
                        id: dateText
                        text: startDate
                        color: "blue"
                        font.pointSize: 14
                        Layout.preferredWidth: colWidth
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                    Text {
                        id: distInKmsText
                        text: distInKms
                        color: "blue"
                        font.pointSize: 14
                        Layout.preferredWidth: colWidth
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                    Text {
                        id: mTimeText
                        text: movingTime
                        color: "blue"
                        font.pointSize: 14
                        Layout.preferredWidth: colWidth
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                    Text {
                        id: avgSpdText
                        text: avgSpdKMsPerHr
                        color: "blue"
                        font.pointSize: 14
                        Layout.preferredWidth: colWidth
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                }
            }
        }
    }
}
