import QtQuick 2.7

Item {
    id: root

    // No explicit width/height given here.
    // Width & height dependant on width/height OR anchors of CONTAINING item...

    width: parent.width
    height: parent.height

    Component.onCompleted: {
        print("Page4: onCompleted:");
        print("   width / height = " + root.width + " / " + root.height);
        print("   implicit wd/ht = " + root.implicitWidth + " / " + root.implicitHeight);
    }

    // Here, the Component must be given BOTH width & height, either
    // explicitly, or, by anchors to root.
    SimpleFixedCenter {
        id: sfcThingy
        anchors.fill: root  // Will resize along with 'root'
    }
}
