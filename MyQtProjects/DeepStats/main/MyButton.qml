import QtQuick 2.0
import QtQml 2.2

Rectangle {
    id: myButton
    property alias text: myText.text
    property alias textColor: myText.color


    signal clicked()

    property color bgColor: "black"
    property color opColor: "black"     //Qt.lighter(bgColor, 1.5);

    width: myText.contentWidth * 1.2
    height: myText.contentHeight * 1.2

    border.width: 2
    border.color: textColor
    radius: 20

    gradient: Gradient {
        GradientStop { position: 0.0; color: opColor }
        GradientStop { position: 1.0; color: bgColor }
    }

    Text {
        id: myText
        text: "Click Me!";
        font.pixelSize: 30;
        font.italic: true;
        font.bold: true;
        color: "green"      // #75FFFF";
        anchors.centerIn: parent
    }

    MouseArea {
        id: ma
        anchors.fill: parent
        onClicked: {
            print("myText button clicked:");
            myButton.clicked()
        }
    }


}
