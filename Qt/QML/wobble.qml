// test for the wobbling password field: on failing to enter correct items
// use with 'qmlscene'
import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TextField {
        id: pwField
        x: 20
        y: 30
        width: 120
        height: 45
        font.pointSize: 14
        placeholderText: "password"
        onTextChanged: {

        }
    }
}
