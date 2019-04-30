import Qt.labs.platform 1.1

SystemTrayIcon {
    id: systemTray
    visible: true

    tooltip: qsTr("Rotatomatic")
    iconSource: "qrc:/icon.png"

    property var preferences: PreferenceDialog {
        remoteSensors: sensorListModel
        outputs: outputListModel
    }

    // Systray Menu
    menu: Menu {
        MenuItem {
            text: qsTr("Preferences...")
            onTriggered: preferences.open()
        }

        MenuSeparator {}
        MenuItem {
            text: qsTr("Quit")
            onTriggered: Qt.quit()
        }
    }
}
