import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5
import me.fuhrmannb.rotatomatic 0.1

GridLayout {
    columns: 2

    property alias name: name.text
    property alias url: url.text
    property alias screen:
    property alias offset: offset.value

    property alias screenModel: screen.model

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

    Image {
        id: image
        Layout.columnSpan: 2
        Layout.alignment: Qt.AlignCenter

        source: "qrc:/android.png"
    }

    Label {
        Layout.alignment: Qt.AlignRight
        text: qsTr("Name:")
    }
    TextField {
        id: name
        text: sensor.url
        placeholderText: "Device name"
    }
    Label {
        Layout.alignment: Qt.AlignRight
        text: qsTr("URL:")
    }
    TextField {
        id: url
        text: sensor.url
        placeholderText: "ws://ip:port"
    }

    Label {
        Layout.alignment: Qt.AlignRight
        text: qsTr("Screen:")
    }
    ComboBox {
        id: screen
        textRole: "display"
    }

    Label {
        Layout.alignment: Qt.AlignRight
        text: qsTr("Offset:")
    }
    SpinBox {
        id: offset
        from: 0
        to: 315
        stepSize: 45
        textFromValue: function(value) {
            return value + "°"
        }
        value: sensor.offset
    }
}
