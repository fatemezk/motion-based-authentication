import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Motion Authentication")

    Column {
        anchors.centerIn: parent

        Button {
            text: "Start"
            onClicked: sensorHandler.start()
        }

        Button {
            text: "Stop"
            onClicked: sensorHandler.stop()
        }


    }
}
