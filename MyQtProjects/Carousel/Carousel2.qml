// Carousel2.qml
import QtQuick 2.1

PathView {
    id: view
    width: 640
    height: 360
    model: 32
    delegate: Text { text: index }

    property int pathMargin: 50
    property real rx: ry // view.width / 2 - pathMargin
    property real ry: view.height / 2 - pathMargin
    property real magic: 0.551784
    property real mx: rx * magic
    property real my: ry * magic
    property real cx: view.width / 2
    property real cy: view.height / 2
    path: Path {
     startX: view.cx + view.rx; startY: view.cy
     PathCubic { // first quadrant arc
     control1X: view.cx + view.rx; control1Y: view.cy + view.my
     control2X: view.cx + view.mx; control2Y: view.cy + view.ry
     x: view.cx; y: view.cy + view.ry
     }
     PathCubic { // second quadrant arc
     control1X: view.cx - view.mx; control1Y: view.cy + view.ry
     control2X: view.cx - view.rx; control2Y: view.cy + view.my
     x: view.cx - view.rx; y: view.cy
     }
     PathCubic { // third quadrant arc
     control1X: view.cx - view.rx; control1Y: view.cy - view.my
     control2X: view.cx - view.mx; control2Y: view.cy - view.ry
     x: view.cx; y: view.cy - view.ry
     }
     PathCubic { // forth quadrant arc
     control1X: view.cx + view.mx; control1Y: view.cy - view.ry
     control2X: view.cx + view.rx; control2Y: view.cy - view.my
     x: view.cx + view.rx; y: view.cy
     }
    }
}
