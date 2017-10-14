import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 1024
    height: 1000
    title: qsTr("Hello World")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            Flickable {
                id: theFlicker
                width: parent.width
                height: parent.height
                contentWidth: parent.width
                contentHeight: (grid2.rows / 3) * 392
                Rectangle {
                    color: "white"
                    anchors.fill: parent
                    anchors.margins: 20
                    GridLayout {
                        id : grid2
                        anchors.fill: parent
                        rows    : 15
                        columns : 12
                        property double colMulti : grid2.width / grid2.columns  // ORIG
                        property double rowMulti : grid2.height / grid2.rows
                        function prefWidth(item){
                            return colMulti * item.Layout.columnSpan      // ORIG
                        }
                        function prefHeight(item){
                            return rowMulti * item.Layout.rowSpan
                        }

                        Component.onCompleted: {
                            console.log("==================================================================");
                            console.log("Col Spacing = " + grid2.columnSpacing);
                            console.log("Grid width  = " + grid2.width);
                            console.log("Grid cols   = " + grid2.columns);
                            console.log("Grid height = " + grid2.height);
                            console.log("Grid contHt = " + theFlicker.contentHeight);
                        }

                        // -----------------------------------------------------------------------------------
                        // NOTE - Layout.preferredWidth  : grid2.prefWidth(this) - (((3-1) * grid2.columnSpacing) / 3)
                        // The bit being subtracted, i.e. (((3-1) * grid2.columnSpacing) / 3)   --- OR ---
                        //                                (((N-1) * grid2.columnSpacing) / N)
                        // Where N is:
                        // The number of cards there will be on this ROW. we subtract 1, because we are REALLY
                        // looking for how many GAPS (of size columnSpacing) there will be on this row.
                        // Also be aware that to keep all same-sized cards the same, N is actually the
                        // 'POTENTIAL' number of cards, at that size, that could fit on a row. Where this
                        // makes a differenre is if there is only 1 card on a row, (at the end, say), then we
                        // still size it as if we filled the row with similar sized cards.
                        //
                        // HMMMMM... We might be able to calculate the preferredWidth multiplication factor
                        //           in the Model, and simply return it based on each item's index... Then,
                        //           all we would need to do multiply by the actual width of the GridLayout.
                        //           or make it a good old fashion function and pass that width in.
                        // -----------------------------------------------------------------------------------


                        // Row 1
                        CardOne {
                            cardColor : 'red'
                            Layout.rowSpan   : 3
                            Layout.columnSpan: 4
                            Layout.preferredWidth  : grid2.prefWidth(this) - (((3-1) * grid2.columnSpacing) / 3)
                            Layout.preferredHeight : grid2.prefHeight(this)

                            Component.onCompleted: {
                                console.log("ROW 1 A WIDTH = " + width);
                            }
                        }
                        CardTwo {
                            title : "This is a small title!"
                            Layout.rowSpan   : 3
                            Layout.columnSpan: 4
                            Layout.preferredWidth  : grid2.prefWidth(this) - (((3-1) * grid2.columnSpacing) / 3)
                            Layout.preferredHeight : grid2.prefHeight(this)
                            Component.onCompleted: {
                                console.log("ROW 1 B WIDTH = " + width);
                            }
                        }
                        CardOne {
                            cardColor : 'green'
                            Layout.rowSpan : 3
                            Layout.columnSpan : 4
                            Layout.preferredWidth  : grid2.prefWidth(this) - (((3-1) * grid2.columnSpacing) / 3)
                            Layout.preferredHeight : grid2.prefHeight(this)
                            Component.onCompleted: {
                                console.log("ROW 1 C WIDTH = " + width);
                            }
                        }


                        // Row 2
                        CardOne {
                            cardColor : 'cyan'
                            Layout.rowSpan   : 3
                            Layout.columnSpan: 4
                            Layout.preferredWidth  : grid2.prefWidth(this) - (((2-1) * grid2.columnSpacing) / 2)
                            Layout.preferredHeight : grid2.prefHeight(this)
                            Component.onCompleted: {
                                console.log("ROW 2 WIDTH = " + width);
                            }
                        }
                        CardOne {
                            cardColor : 'magenta'
                            Layout.rowSpan   : 3
                            Layout.columnSpan: 8
                            Layout.preferredWidth  : grid2.prefWidth(this) - (((2-1) * grid2.columnSpacing) / 2)
                            Layout.preferredHeight : grid2.prefHeight(this)
                        }

                        // Row 3
                        CardOne {
                            cardColor : 'yellow'
                            Layout.rowSpan : 3
                            Layout.columnSpan : 6
                            Layout.preferredWidth  : grid2.prefWidth(this) - (((2-1) * grid2.columnSpacing) / 2)
                            Layout.preferredHeight : grid2.prefHeight(this)
                            Component.onCompleted: {
                                console.log("ROW 3 WIDTH = " + width);
                            }
                        }

                        // Row 4
                        CardTwo {
                            title : 'A WAY bigger title can fit on a bigger card!'
                            Layout.rowSpan : 3
                            Layout.columnSpan : 12
                            Layout.preferredWidth  : grid2.prefWidth(this) - (((1-1) * grid2.columnSpacing) / 1)
                            Layout.preferredHeight : grid2.prefHeight(this)
                            Component.onCompleted: {
                                console.log("ROW 4 WIDTH = " + width);
                            }
                        }

                        // Row 5
                        CardOne {
                            cardColor : 'orange'
                            Layout.rowSpan : 3
                            Layout.columnSpan : 8
                            Layout.preferredWidth  : grid2.prefWidth(this) - (((2-1) * grid2.columnSpacing) / 2)
                            Layout.preferredHeight : grid2.prefHeight(this)
                            Component.onCompleted: {
                                console.log("ROW 5 WIDTH = " + width);
                            }
                        }
                        CardOne {
                            cardColor : '#0000EE'
                            Layout.rowSpan : 3
                            Layout.columnSpan : 4
                            Layout.preferredWidth  : grid2.prefWidth(this) - (((2-1) * grid2.columnSpacing) / 2)
                            Layout.preferredHeight : grid2.prefHeight(this)
                        }
                    }
                }
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
//        TabButton {
//            text: qsTr("Second")
//        }
    }
}
