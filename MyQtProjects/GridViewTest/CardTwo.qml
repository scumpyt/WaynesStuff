import QtQuick 2.0

Rectangle {
    id: cardTwo
    color: "black"
    property string title: ""

    Rectangle {
        color: "white"
        anchors.fill: parent
        anchors.margins: 10

        Text {
            text: title
            color: "blue"
            anchors.centerIn: parent
            font {
                pixelSize: 20
                bold: true
            }
        }
    }
}
