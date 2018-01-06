import QtQuick 2.7

Item {
    id: root

    // No explicit width/height given here.
    // Width & height dependant on width/height OR anchors of CONTAINING item...

    Component.onCompleted: {
        print("Page3: onCompleted:");
        print("   width / height = " + root.width + " / " + root.height);
        print("   implicit wd/ht = " + root.implicitWidth + " / " + root.implicitHeight);
    }

    // Here, the Component must be given BOTH width & height, either
    // explicitly, or, by anchors to root.
    SimpleResizableTwo {
        anchors.fill: root  // Will resize along with 'root'
    }

}

