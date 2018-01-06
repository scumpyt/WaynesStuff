// Carousel0.qml
import QtQuick 2.1

PathView {
    id: view
    width: 640
    height: 360
    model: 32
    delegate: Text { text: index }
    path: Path {
        startX: 0
        startY: 0
        PathLine { x: view.width; y: view.height }
    }
}
