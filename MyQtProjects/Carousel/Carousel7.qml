// Carousel7.qml
import QtQuick 2.5
import QtQuick.Layouts 1.1

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


//    PathView {
//        id: view
//        width: parent.width
//        height: parent.height + y
//        //y: –33

//        model: theModel

//        delegate: circleDelegate

//        path: Ellipse {
//            width: view.width
//            height: view.height - 100
//        }

//        //pathItemCount: 3
//        snapMode: PathView.SnapToItem

//        focus: true
//        Keys.onLeftPressed: decrementCurrentIndex()
//        Keys.onRightPressed: incrementCurrentIndex()
//    }

    ListView
    {
        id: view

        // VERTICAL...
//        width: 200
//        height: parent.height

        y: 100

        // HORIZONTAL...
        width: parent.width
        height: 200

        anchors.centerIn: parent

        model: theModel

        delegate: circleDelegate

        orientation: ListView.Horizontal
//        layoutDirection: Qt.LeftToRight
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

            scale: 4. * y / parent.height
            //scale: 6. * y / parent.height
            //scale: PathView.isCurrentItem ? 4 :  4. * y / parent.height

            z: y
            smooth: true
            opacity: scale / 2.

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
        }
    }
}

