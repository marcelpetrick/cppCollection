// test for the wobbling password field: on failing to enter correct items
// use with 'qmlscene'
import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: window
    visible: true
    width: 666
    height: 333
    //move it to a proper centered position
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2

    color: "#860606"
    title: qsTr("Hello World")

    TextField {
        id: pwField
        anchors.horizontalCenter: window.anchor.horizontalCenter
//        x: 50
//        y: 50
        width: 180
        height: 50
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
                    console.log("proper input!")
                    pwTrue.start()
                } else {
                    console.log("reset now")
                    text = ""
                    animation.start()
                }
            }
        }

        SequentialAnimation
        {
//            property int shiftDistance: 50;
            id: pwTrue;
            PropertyAnimation {
                target: pwField.anchors.horizontalCenterOffset;
                property: "x";
                to: -50;
                duration: 222 }
            PropertyAnimation {
                target: pwField.anchors.horizontalCenterOffset;
                property: "x";
                to: 2*50;
                duration: 222 }
            PropertyAnimation {
                target: pwField.anchors.horizontalCenterOffset;
                property: "x";
                to: -50/2;
                duration: 222 }
            PropertyAnimation {
                target: pwField.anchors.horizontalCenterOffset;
                property: "x";
                to: 50;
                duration: 222 }
        }

        RotationAnimation on rotation {
            id: animation
            running: false
            loops: 2 //Animation.Infinite
            from: 0
            to: 360
        }
    }

    Rectangle {
        id: theRect
        width: 100
        height: 100
        x: 400
        y: 200
        color: "blue"

        // this is a standalone animation, it's not running by default
        SequentialAnimation
        {
            id: rectAni;
            PropertyAnimation {
                target: theRect;
                property: "x";
                to: 300;
                duration: 500 }
            PropertyAnimation {
                target: theRect;
                property: "x";
                to: 100;
                duration: 500 }
        }

        MouseArea { anchors.fill: parent; onClicked: rectAni.running = true }
    }
}
