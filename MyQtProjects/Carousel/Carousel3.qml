// Carousel3.qml
import QtQuick 2.1

PathView {
    id: view
    width: 640
    height: 360
    model: 32
    delegate: Text { text: index }
    path: Ellipse {
        width: view.width
        height: view.height
    }
}
