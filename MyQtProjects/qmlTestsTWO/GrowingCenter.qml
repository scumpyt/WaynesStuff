import QtQuick 2.7
import QtQuick.Layouts 1.1

/////////////////////////////////////////////////////////////////////////////
// This example shows how to create a widget that can grow when resized,
// BUT, will only SHRINK down to a minimum size.
//
// This was insanely difficult for me to get right, and I still have no idea
// it's the best way. But it actually works... FINALLY!!!
/////////////////////////////////////////////////////////////////////////////

Item {
    id: root
    property int myMargin: 20

    width: centralLayout.implicitWidth + 2 * myMargin
    height: centralLayout.implicitHeight + 2 * myMargin
    Layout.minimumWidth: centralLayout.Layout.minimumWidth + 2 * myMargin
    Layout.minimumHeight: centralLayout.Layout.minimumHeight + 2 * myMargin

    RowLayout {
        id: centralLayout

        anchors {
            fill: parent
            margins: myMargin
        }

        Rectangle {
            id: centralContainer
            width: parent.width
            height: 100

            // THESE ARE KEY TO SETTING THE MIN WID/HT !!!
            Layout.minimumWidth: innerRow.implicitWidth + (4 * myMargin)
            Layout.minimumHeight: 100

            // THIS IS KEY TO IT GROWING TO OCCUPY SPACE!!!
            Layout.fillWidth: true

            color: "transparent"
            radius: 20
            border {
                width: 2
                color: "red"
            }

            RowLayout {
                id: innerRow
                anchors {
                    fill: parent
                    margins: myMargin       // ???
                }

                Rectangle {
                    id: leftCircle
                    width: centralContainer.height * 0.8
                    height: centralContainer.height * 0.8
                    radius: width/2
                    color: "blue"
                    Layout.fillWidth: false
                    anchors {
                        verticalCenter: innerRow.verticalCenter
                    }
                }

                Text {
                    id: centralText
                    text: "This is the central text!"
                    font {
                        pixelSize: 30
                    }
                    anchors {
                        verticalCenter: innerRow.verticalCenter
                        left: leftCircle.right
                    }
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment:   Text.AlignVCenter
                    color: "blue"
                    Layout.fillWidth: true
                }

                Rectangle {
                    id: rightCircle
                    width: centralContainer.height * 0.8
                    height: centralContainer.height * 0.8
                    radius: width/2
                    color: "blue"
                    Layout.fillWidth: false
                    anchors {
                        verticalCenter: innerRow.verticalCenter
                        left: centralText.right
                    }
                }
            }
        }
    }
}
