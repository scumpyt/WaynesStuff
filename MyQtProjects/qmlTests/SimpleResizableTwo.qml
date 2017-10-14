import QtQuick 2.7

///////////////////////////////////////////////////////////////////////////////////////
// This is an example of a custom Component whose intention is to resize to it's
// CONTAINER. Notice that:
//    - No explicit width/height are set.
//    - The width/height of the Rectangles are based on 'root's width/height
//
// This is essentially the same as SimpleResizable, but uses anchors instead of
// setting x & y explicitly...
///////////////////////////////////////////////////////////////////////////////////////

Item {
    id: root

    Component.onCompleted: {
        print("SimpleResizableTwo: onCompleted:");
        print("   width / height = " + root.width + " / " + root.height);
        print("   implicit wd/ht = " + root.implicitWidth + " / " + root.implicitHeight);
    }

    Rectangle {
        id: topLeftRect
        width: root.width * 0.2
        height: root.height * 0.2
        color: 'magenta'
    }
    Rectangle {
//        x: 0.2 * root.width
//        y: 0.2 * root.height

        width: root.width * 0.8
        height: root.height * 0.8
        color: 'cyan'

        anchors {
            top: topLeftRect.bottom
            left: topLeftRect.right
        }
    }
}

