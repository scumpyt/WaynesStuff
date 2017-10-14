import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 1000
    height: 800
    title: qsTr("Hello World")

    ////////////////////////////////////////////////////////////////////////
    // For these tests, the parent container is the SwipeView. It is set to
    // "anchors.fill: parent" - The probably has the same influence as a
    // StackView. I.e. All of the top-level children will ALSO be
    // "anchors.fill: parent". (I'm not 100% sure of this... it is QML,
    // afterall, but I think that's how it works...)
    // So, each page occupies one 'page' of the SwipeView...
    ////////////////////////////////////////////////////////////////////////
    SwipeView {
        id: swipeView
        anchors.fill: parent

        currentIndex: tabBar.currentIndex

//        Page1 {
//            // By default, will FILL parent - BECAUSE SwipeView is already anchored
//            // anchors.fill: parent // *** trying to set it here IS ERROR, because conflicts with SwipeView anchor
//        }

//        SimpleResizable {
//            // By default, will FILL parent
//        }

//        Page {
//            // By default, will FILL parent, I think
//            SimpleResizable {
//                anchors.fill: parent
//            }
//        }

//        Page {
//            SimpleResizable {
//                width: 200
//                height: 300
//            }
//        }

//        Page {
//            SimpleResizable {
//                height: 300
//                anchors {
//                    left: parent.left
//                    right: parent.right
//                }
//            }
//        }

//        Page {
//            SimpleResizable {
//                width: 200
//                anchors {
//                    top: parent.top
//                    bottom: parent.bottom
//                }
//            }
//        }

//        Page2 {
//        }

//        Page {
//            id: compPage
//            Component.onCompleted: {
//                print("COMP: onCompleted:");
//                print("   width / height = " + compPage.width + " / " + compPage.height);
//                print("   implicit wd/ht = " + compPage.implicitWidth + " / " + compPage.implicitHeight);
//            }

//            Page1 {
//                width: parent.width / 2
//                height: parent.height
//                anchors {
//                    left: parent.left
//                }
//            }
//            Page2 {
//                width: parent.width / 2
//                height: parent.height
//                anchors {
//                    right: parent.right
//                }
//            }
//        }

//        Page3 {
//        }

        Page4 {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
//        TabButton {
//            text: qsTr("Page1")
//        }
//        TabButton {
//            text: qsTr("SimpleResizable")
//        }
//        TabButton {
//            text: qsTr("FULL")
//        }
//        TabButton {
//            text: qsTr("FIXED")
//        }
//        TabButton {
//            text: qsTr("FIXED WD")
//        }
//        TabButton {
//            text: qsTr("FIXED HT")
//        }
//        TabButton {
//            text: qsTr("Page2")
//        }
//        TabButton {
//            text: qsTr("COMP")
//        }
//        TabButton {
//            text: qsTr("Page3")
//        }
        TabButton {
            text: qsTr("Page4")
        }
    }
}



