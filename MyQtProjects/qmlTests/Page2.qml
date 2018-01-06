import QtQuick 2.7

// In this example, we lay out 2 SimpleResizable's, one in each, opposite corner...
Item {
    id: root

    // No explicit width/height given here.
    // Width & height dependant on width/height OR anchors of CONTAINING item...

    Component.onCompleted: {
        print("Page2: onCompleted:");
        print("   width / height = " + root.width + " / " + root.height);
        print("   implicit wd/ht = " + root.implicitWidth + " / " + root.implicitHeight);
    }

    SimpleResizable {
        id: topLeftCorner
        width: root.width / 2
        height: root.height / 2
        anchors {
            top: root.top
            left: root.left
        }
    }

    SimpleResizable {
        id: bottomRightCorner
        width: root.width / 2
        height: root.height / 2
        anchors {
            bottom: root.bottom
            right: root.right
        }
    }
}
