import QtQuick 2
import QtQuick.Window 2

Window {
    id: window
    visible: true
    title: qsTr("lvgl_qt_quick")
    property int tick_period_ms: 0
    property int swap: 0

    // `image.source` has been binded to `swap`, so updating `swap` re-runs `requestPixmap`.
    //  Disable caching to call into `LvglImageProvider::requestPixmap` each time.
    Image {
        id: image
        anchors.fill: parent
        source: "image://LvglImageProvider/buf" + swap
        cache: false
    }

    Timer {
        interval: tick_period_ms
        running: true
        repeat: true
        onTriggered: swap = (swap ? 0 : 1)
    }
}
