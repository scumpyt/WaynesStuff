import QtQuick 2.7

///////////////////////////////////////////////////////////////////////////////////////
// This is an example of a custom Component whose intention is to resize to it's
// CONTAINER. Notice that:
//    - No explicit width/height are set.
//    - The width/height of the Rectangles are based on 'root's width/height
///////////////////////////////////////////////////////////////////////////////////////

Item {
    id: root

    Component.onCompleted: {
        print("SimpleFixedCenter: onCompleted:");
        print("   width / height = " + root.width + " / " + root.height);
        print("   implicit wd/ht = " + root.implicitWidth + " / " + root.implicitHeight);
    }

    Rectangle {
        id: backgroundRect
        width: root.width
        height: root.height
        color: 'yellow'

        Component.onCompleted: {
            print("backgroundRect: onCompleted:");
            print("   width / height = " + backgroundRect.width + " / " + backgroundRect.height);
            print("   implicit wd/ht = " + backgroundRect.implicitWidth + " / " + backgroundRect.implicitHeight);
        }

        Rectangle {
            id: centralContainer
            // width: root.width * 0.8
            width: Math.max(root.width * 0.8, (centralText.width + (2 * (height*0.8)) + 40))
            height: 100
            anchors.centerIn: backgroundRect
            color: "transparent"
            radius: 20
            border {
                width: 2
                color: "red"
            }

            Component.onCompleted: {
                print("centralContainer: onCompleted:");
                print("   width / height = " + centralContainer.width + " / " + centralContainer.height);
                print("   implicit wd/ht = " + centralContainer.implicitWidth + " / " + centralContainer.implicitHeight);
            }

            Rectangle {
                id: leftCircle
                width: centralContainer.height * 0.8
                height: centralContainer.height * 0.8
                anchors {
                    left: centralContainer.left
                    leftMargin: 10
                    verticalCenter: centralContainer.verticalCenter
                }
                radius: width/2
                color: "blue"
            }

            Text {
                id: centralText
                text: "This is the central text!"
                font {
                    pixelSize: 30
                }
                anchors {
                    centerIn: centralContainer
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment:   Text.AlignVCenter
                color: "blue"
            }

            Rectangle {
                id: rightCircle
                width: centralContainer.height * 0.8
                height: centralContainer.height * 0.8
                anchors {
                    right: centralContainer.right
                    rightMargin: 10
                    verticalCenter: centralContainer.verticalCenter
                }
                radius: width/2
                color: "blue"
            }
        }
    }
}

