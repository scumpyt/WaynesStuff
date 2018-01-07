import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

import ca.scumpyware.deepstats 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 1000
    //color: "lightblue"
    title: qsTr("Deep Stats")

    /////////////////////////////////////////////////////////////////////////
    // Application-wide window-footer linked to the current SwipeView page...
    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        //currentIndex: 2       // To test Test Stuff...
        TabButton {
            text: qsTr("My Rides")
        }
        TabButton {
            text: qsTr("Ride Summaries")
        }
        TabButton {
            text: qsTr("Test Stuff")
        }
    }

    /////////////////////////////////////////
    // All pages can share the same Portal...
    StravaPortal
    {
        id: thePortal

        Component.onCompleted: {
            thePortal.fetchActivities();
        }

        onActivitiesModelUpdated: {
            //print("PORTAL ACTIVITIES MODEL UPDATED: " );
            listPage.listPageModel = thePortal.portalActivitiesModel;
        }

        // (NOTE - the body of signal handlers in QML uses JavaScript)
        onNewSummaryAvailable: {
//            print("NEW SUMMARY AVAILABLE: " );

            var vMap = thePortal.getSummaryVMap();
//            print("totalRides = " + vMap["totalRides"]);
//            print("totalDist  = " + vMap["totalDist"]);

            summPage.numRides  = vMap["totalRides"];
            summPage.totDist   = vMap["totalDist"];
            summPage.avgDist   = vMap["avgDist"];
            summPage.medDist   = vMap["medianDist"];
            summPage.totMTime  = vMap["totalMovingTimeHMS"];
            summPage.avgMTime  = vMap["avgMovingTimeHMS"];
            summPage.medMTime  = vMap["medianMovingTimeHMS"];
            summPage.longRide  = vMap["longestRideDist"];
            summPage.longMTime = vMap["longestRideTimeHMS"];
        }
    }

    //////////////////////////////////////
    // Main Page control is a SwipeView...
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        //////////////////////////////////////////////
        // This Page is the List of Activities Page...
        Page {
            ListPage {
                id: listPage
                anchors.fill: parent
                onDoSort: {
                    print("DO SORT CAUGHT!!! : " + sortFieldStr);
                    thePortal.sort(sortFieldStr)
                }
            }
        }

        //////////////////////////////////
        // This Page is the SummaryPage...
        Page {
            SummaryPage {
                id: summPage
                anchors.fill: parent
                onDoSummarize: {
                    //print("DO SUMMARIZE CAUGHT!!! : " + startDateStr + " TO " + endDateStr)
                    thePortal.summarize(startDateStr, endDateStr);
                }
            }
        }

        //////////////////////////////////
        // This Page is currently just to test stuff...
        Page {
            Rectangle {
                id: topLevelCont
                anchors.fill: parent
                color: "black"
                Item {
                    id: dates

                    // NOTE: Property binding code in QML uses JavaScript!
                    width: calCompStart.width + calCompEnd.width
                    height: Math.max(calCompStart.height, calCompEnd.height)

                    anchors.topMargin: 20
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter

                    RowLayout {
                        spacing: 10
                        CalendarComponent {
                            id: calCompStart
                            width: 250
                            height: 150
                            promptText: "Set Start Date"
                            promptPixelSize: 24
                            promptColor: "purple"
                        }

                        CalendarComponent {
                            id: calCompEnd
                            width: 250
                            height: 150
                            promptText: "Set End Date"
                            promptPixelSize: 24
                            promptColor: "green"
                        }
                    }
                }

                Rectangle {
                    id: theRect
                    width: 500
                    height: 300
                    color: "lightblue"
                    anchors.top: dates.bottom
                    anchors.horizontalCenter: dates.horizontalCenter
                    border.color: "red"
                    border.width: 3
                }


                MyButton {
                    id: shortBtn
                    anchors {
                        top: theRect.bottom
                        topMargin: 50
                        horizontalCenter: theRect.horizontalCenter
                    }

                    text: 'Short'
                    onClicked: {
                        print ("MyButton caught in page...")
                    }
                }

                MyButton {
                    id: longBtn
                    anchors {
                        top: shortBtn.bottom
                        topMargin: 50
                        horizontalCenter: theRect.horizontalCenter
                    }

                    textColor: "white"
                    text: 'A very much, much longer amount of text'
                    onClicked: {
                        print ("MyButton caught in page...")
                    }
                }
            }
        }
    }   // SwipeView
}
