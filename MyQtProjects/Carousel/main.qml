import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
//    width: 640
//    height: 480
    width: 1000
    height: 800
    title: qsTr("Hello World")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            //Carousel0 {}
            //Carousel1 {}
            //Carousel2 {}
            //Carousel3 {}
            //Carousel4 {}
            //Carousel5 {}
            Carousel6 {}
        }

        Page1 {
            //Carousel0 {}
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
