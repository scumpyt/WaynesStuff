import QtQuick 2.0

Rectangle {
    id: cardOne
    color: "black"
    property string cardColor: ""

    Rectangle {
        color: cardColor
        anchors.fill: parent
        anchors.margins: 10
    }
}
