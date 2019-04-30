import QtQuick 2.0

import QtQuick.Layouts 1.12

Item {
    height: 36

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

    Image {
        id: sensorImage
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        source: "qrc:/android.png"
    }
    Text {
        id: sensorText
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: sensorImage.right
        text: display
        color: myPalette.text
    }
}
