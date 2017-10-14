import QtQuick 2.7

// In this example, the 2 rects will grow in proportion to the
// (resizable) height/width of root.
Item {
    id: root

    // No explicit width/height given here.
    // Width & height dependant on width/height OR anchors of CONTAINING item...

    Component.onCompleted: {
        print("Page1: onCompleted:");
        print("   width / height = " + root.width + " / " + root.height);
        print("   implicit wd/ht = " + root.implicitWidth + " / " + root.implicitHeight);
    }

    SimpleResizable {
        anchors.fill: root  // Will resize along with 'root'
    }
}
