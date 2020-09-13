import QtQuick 2
import QtQuick.Window 2

Window {
    id: window
    visible: true
    title: qsTr("lvgl_qt_quick")
    property int swap: 0

    // `image.source` has been binded to `swap`, so updating `swap` re-runs `requestPixmap`.
    //  Disable caching to call into `LvglImageProvider::requestPixmap` each time.
    Image {
        id: image
        anchors.fill: parent
        source: "image://LvglImageProvider/buf" + swap
        cache: false

        MouseArea {
            id: mouseArea
            objectName: "mouseArea"
            anchors.fill: parent
        }
    }

    Timer {
        id: timer
        objectName: "timer"
        running: true
        repeat: true
        onTriggered: swap = (swap ? 0 : 1)
    }
}
