// test for the wobbling password field: on failing to enter correct items
// use with 'qmlscene'
import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: window
    visible: true
    width: 400
    height: 300
    //move it to a proper centered position
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2

    color: "#860606"
    title: qsTr("Hello World")

    TextField {
        id: pwField
        x: 50
        y: 50
        width: 180
        height: 45
        antialiasing: true
        rotation: 10
        transformOrigin: Item.Center
        font.pointSize: 20
        echoMode: 2
        placeholderText: "password"
        maximumLength: 4
        onTextChanged: {
            if (text.length === 4) {
                console.log("length 4 reached")

                if (text === "aaaa") {
                    console.log("proper!")
                } else {
                    console.log("reset now")
                    text = ""
                    animation.start()
                }
            }
        }

        RotationAnimation on rotation {
            id: animation
            running: false
            loops: 2 //Animation.Infinite
            from: 0
            to: 360
        }
    }
}
