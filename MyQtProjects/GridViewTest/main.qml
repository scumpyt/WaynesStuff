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

        Page1 {
            GridLayout {
                id : grid
                anchors.fill: parent
                rows    : 12
                columns : 12
                property double colMulti : grid.width / grid.columns
                property double rowMulti : grid.height / grid.rows
                function prefWidth(item){
                    return colMulti * item.Layout.columnSpan
                }
                function prefHeight(item){
                    return rowMulti * item.Layout.rowSpan
                }

                Rectangle {
                    color : 'red'
                    Layout.rowSpan   : 10
                    Layout.columnSpan: 2
                    Layout.preferredWidth  : grid.prefWidth(this)
                    Layout.preferredHeight : grid.prefHeight(this)
                }
                Rectangle {
                    color : 'yellow'
                    Layout.rowSpan   : 10
                    Layout.columnSpan: 10
                    Layout.preferredWidth  : grid.prefWidth(this)
                    Layout.preferredHeight : grid.prefHeight(this)
                }
                Rectangle {
                    id : greenRect
                    color : 'green'
                    Layout.rowSpan : 2
                    Layout.columnSpan : 12
                    Layout.preferredWidth  : grid.prefWidth(this)
                    Layout.preferredHeight : grid.prefHeight(this)
                }
            }
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
