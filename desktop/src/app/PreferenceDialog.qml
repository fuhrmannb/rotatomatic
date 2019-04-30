import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.12
import me.fuhrmannb.rotatomatic 0.1

// Preferences
Dialog {
    id: preferences
    title: qsTr("Rotatomatic Preferences")
    standardButtons: StandardButton.Ok | StandardButton.Apply | StandardButton.Cancel

    width: 500
    height: 300

    property var remoteSensors: SensorListModel
    property var outputs: OutputListModel

    property var emptySensor: RemoteSensor{}
    function currentSensor() {
        var rs = remoteSensors.get(sensorListView.currentIndex)
        return rs === null ? emptySensor : rs
    }

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

    // Need a nested item to anchors work perfecly (avoid implicitHeight loop). Qt bug?
    Item {
        anchors.fill: parent
        ListView {
            id: sensorListView
            width: 200
            anchors {
                top: parent.top
                left: parent.left
                bottom: addButton.top
            }

            model: remoteSensors

            delegate: SensorDelegate {
                anchors {
                    left: parent.left
                    right: parent.right
                }

                // Background color that appears on mouse hover on a item
                Rectangle {
                    id: sensorHover
                    anchors.fill: parent
                    radius: 1
                    color: myPalette.highlight
                    z: -1
                    opacity: 0
                }

                // Manage mouse selection and hover
                MouseArea {
                    anchors.fill: parent
                    onClicked: sensorListView.currentIndex = index
                    hoverEnabled: true
                    onEntered: { sensorHover.opacity = 0.4 }
                    onExited: { sensorHover.opacity = 0 }
                }
            }
            highlight: Rectangle { color: myPalette.highlight; radius: 1 }
        }

        Item {
            anchors {
                top: parent.top
                left: sensorListView.right
                right: parent.right
                bottom: parent.bottom
            }

            RemoteSensorView {
                anchors.horizontalCenter: parent.horizontalCenter
                sensor: currentSensor()
                screenModel: outputs

                visible: sensorListView.count > 0
            }
        }

        Button {
            id: addButton
            text: qsTr("+")

            width: 36
            height: 36

            anchors {
                right: removeButton.left
                bottom: parent.bottom
            }

            onClicked: {
                addDevice.open()
            }
        }
        Button {
            id: removeButton
            text: qsTr("-")

            width: 36
            height: 36

            anchors {
                right: sensorListView.right
                bottom: parent.bottom
            }

            enabled: sensorListView.count > 0
            onClicked: {
                if (sensorListView.count > 0) {
                    removeDevice.open()
                }
            }
        }
    }

    onYes: this.close()
    onNo: this.close()

    Dialog {
        id: addDevice
        width: 300
        height: 400

        title: qsTr("Rotatomatic Preferences")
        standardButtons: StandardButton.Cancel | StandardButton.Ok

        GridLayout {
            columns: 2

            Label {
                text: qsTr("Name:")
            }
            TextField {
                id: addDeviceName
            }

            Label {
                text: qsTr("Device URL:")
            }
            TextField {
                id: addDeviceURL
            }
        }

        onAccepted: {
            remoteSensors.add(addDeviceName.text, addDeviceURL.text)
            console.log("Device added: " + addDeviceName.text + " - " + addDeviceURL.text)
            this.close()
        }
        onRejected: this.close()
    }

    MessageDialog {
        id: removeDevice
        title: qsTr("Remove device")
        text: qsTr("Are you sure to remove the device \"" + currentSensor().name + "\" :")
        standardButtons: StandardButton.Yes | StandardButton.No

        onYes: {
            remoteSensors.remove(sensorListView.currentIndex)
            console.log("Device removed")
            this.close()
        }
        onNo: this.close()
    }
}
