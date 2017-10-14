import QtQuick 2.7
import QtQuick.Layouts 1.1

// In this example, the 2 rects will grow in proportion to the
// (resizable) height/width of root.
Item {
    id: root

//    width: centralLayout.implicitWidth
//    height: centralLayout.implicitHeight
//    Layout.minimumWidth: centralLayout.Layout.minimumWidth
//    Layout.minimumHeight: centralLayout.Layout.minimumHeight

    Component.onCompleted: {
        print("Page1: onCompleted:");
        print("   width / height = " + root.width + " / " + root.height);
        print("   implicit wd/ht = " + root.implicitWidth + " / " + root.implicitHeight);
    }

    Rectangle {
        anchors.fill: root  // Will resize along with 'root'
        color: "red"
    }

}
