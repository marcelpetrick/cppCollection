// test for the wobbling password field: on failing to enter correct items
// use with 'qmlscene'
import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: window
    visible: true
    width: 400
    height: 300
    color: "#860606"
    title: qsTr("Hello World")

    TextField {
        id: pwField
        x: 50
        y: 50
        width: 180
        height: 45
        antialiasing: true
        //rotation: 10
        //transformOrigin: Item.Center
        font.pointSize: 20
        echoMode: 2
        placeholderText: "password"
        maximumLength: 4
        onDataChanged: if (text === "aaaa") {
                           console.log("proper!")
                       }
        onTextChanged: {

        }
    }
}
