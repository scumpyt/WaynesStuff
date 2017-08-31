// Carousel6.qml
import QtQuick 2.1

Rectangle {
    width: parent.width - 120
    height: parent.height -120

    anchors.centerIn: parent
    //color: "grey"

    ListModel {
        id: theModel
        ListElement { title: "007";         iconSource: "007_48px.png" }
        ListElement { title: "Batman";      iconSource: "Batman_48px.png" }
        ListElement { title: "Canada";      iconSource: "Canada_48px.png" }
        ListElement { title: "Lego";        iconSource: "Lego_48px.png" }
        ListElement { title: "Gmail";       iconSource: "Gmail_48px.png" }
        ListElement { title: "Facebook";    iconSource: "Facebook_48px.png" }
        ListElement { title: "Hockey";      iconSource: "Hockey_48px.png" }
        ListElement { title: "LinkedIn";    iconSource: "LinkedIn_48px.png" }
        ListElement { title: "Skype";       iconSource: "Skype_48px.png" }
        ListElement { title: "Tank";        iconSource: "Tank_48px.png" }
        ListElement { title: "Twitter";     iconSource: "Twitter_48px.png" }
    }

    PathView {
        id: view
        anchors.fill: parent
        highlight: appHighlight
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        focus: true
        model: theModel
        delegate: circleDelegate
        path: Path {
            startX: -1500
            startY: height/2 + 50
            PathAttribute { name: "iconScale"; value: 0.25 }

            PathLine { x: width/2; y: height/2; }
            PathAttribute { name: "iconScale"; value: 3.0 }

            PathLine { x: width+1500; y: height/2 + 50; }
            PathAttribute { name: "iconScale"; value: 0.25 }
        }

        onMovementEnded: {
            console.log("onMovementEnded...")
        }
    }



    Component {
        id: appHighlight
        Rectangle { width: 300; height: 300; color: "lightsteelblue" }
    }

    Component
    {
        id: circleDelegate
        Rectangle
        {
            id: theCircle
            width: theImage.width * 2
            height: theImage.height * 2
            color: PathView.isCurrentItem ? "#CCFF00" : "yellow"
            radius: width/2
            border.color: "black"

            //scale: 4. * y / parent.height
            //scale: 6. * y / parent.height
            //scale: PathView.isCurrentItem ? 4 :  4. * y / parent.height
            scale: PathView.iconScale

            //z: y
            z: PathView.isCurrentItem ? 100 : 1     // Make sure center obj is on top
            smooth: true
            opacity: scale / 3

            Image
            {
                id: theImage
                source: iconSource
                width: 48
                height: 48
                anchors.centerIn: parent
            }
            Text
            {
                text: title
                font {
                    pixelSize: 12
                }

                anchors {
                    top: theImage.bottom
                    horizontalCenter: theImage.horizontalCenter
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: view.currentIndex = index
            }


        }
    }
}


