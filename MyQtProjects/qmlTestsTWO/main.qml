import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    property int myMargin: 20

    width: centralLayout.implicitWidth + 2 * myMargin
    height: centralLayout.implicitHeight + 2 * myMargin
    minimumWidth: centralLayout.Layout.minimumWidth + 2 * myMargin
    minimumHeight: centralLayout.Layout.minimumHeight + 2 * myMargin

    title: qsTr("Hello World")

    ////////////////////////////////////////////////////////////////////////
    // For these tests...
    ////////////////////////////////////////////////////////////////////////

    GrowingCenter {
        id: centralLayout
        anchors.fill: parent
    }
}
