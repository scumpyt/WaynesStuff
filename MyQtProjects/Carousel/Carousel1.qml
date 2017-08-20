// Carousel1.qml
import QtQuick 2.1

PathView {
    id: view
    width: 640
    height: 360
    model: 32
    delegate: Text { text: index }

    property int pathMargin: 50
    path: Path {
        startX: pathMargin
        startY: pathMargin
        PathLine { x: view.width - pathMargin; y: pathMargin }
        PathLine { x: view.width - pathMargin; y: view.height - pathMargin }
        PathLine { x: pathMargin; y: view.height - pathMargin }
        PathLine { x: path.startX; y: path.startY }
    }
}
