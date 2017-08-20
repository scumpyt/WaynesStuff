// Carousel4.qml
import QtQuick 2.1

Rectangle {
    width: 700
    height: 500
    color: "grey"

    ListModel {
        id: theModel
        ListElement { title: "007";         iconSource: "007_48px.png" }
        ListElement { title: "Batman";      iconSource: "Batman_48px.png" }
        ListElement { title: "Canada";      iconSource: "Canada_48px.png" }
        ListElement { title: "Lego";        iconSource: "Lego_48px.png" }
        ListElement { title: "Gmail";       iconSource: "Gmail_48px.png" }
        ListElement { title: "Facebook";    iconSource: "Facebook_48px.png" }
//        ListElement { title: "Hockey";      iconSource: "Hockey_48px.png" }
//        ListElement { title: "LinkedIn";    iconSource: "LinkedIn_48px.png" }
//        ListElement { title: "Skype";       iconSource: "Skype_48px.png" }
//        ListElement { title: "Tank";        iconSource: "Tank_48px.png" }
//        ListElement { title: "Twitter";     iconSource: "Twitter_48px.png" }
    }

    PathView {
        id: view
        width: parent.width
        height: parent.height + y
        //y: –33

        model: theModel

        delegate: Image {
            source: iconSource
            width: 48
            height: 48
            scale: 4. * y / parent.height
            z: y
            smooth: true
            opacity: scale / 2.
        }

        path: Ellipse {
            width: view.width
            height: view.height
        }
    }
}
