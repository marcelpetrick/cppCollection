// test for the wobbling password field: on providing correct items it should move sideways a bit
// use with 'qmlscene' (changed: full app now)
import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 1.4 // 2.12

Window {
    id: window
    visible: true
    width: 800
    height: 600
    //move it to a proper centered position
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2

    color: "#860606"
    title: qsTr("password shaker: enter the characters")

    Item {
        id: innerItem
        width: window.width
        height: window.height
    }

    TextField {
        text: "marker"
        anchors.left: pwField.left
    }

    TextField {
        id: pwField
        anchors.horizontalCenter: innerItem.horizontalCenter
        anchors.verticalCenter: innerItem.verticalCenter
        width: 180
        height: 50
        antialiasing: true
//        rotation: 10
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
                    pwFalse.start()
                    text = ""
                } else {
                    console.log("reset now")
                    text = ""
                    animation.start()
                }
            }
        }

//        SequentialAnimation {
//            id: pwFalse;
//            readonly property int shiftDistance: 50
//            readonly property int wobbleTime: 150 // 400
//            PropertyAnimation { target: pwField; property: "anchors.horizontalCenterOffset";
//                to: -pwFalse.shiftDistance; duration: pwFalse.wobbleTime
//            }
//            //PauseAnimation { duration: 300 }
//            PropertyAnimation { target: pwField; property: "anchors.horizontalCenterOffset";
//                to: pwFalse.shiftDistance; duration: 2 * pwFalse.wobbleTime
//            }
//            //PauseAnimation { duration: 300 }
//            PropertyAnimation { target: pwField; property: "anchors.horizontalCenterOffset";
//                to: 0; duration: pwFalse.wobbleTime
//            }
//            //PauseAnimation { duration: 300 }
//            PropertyAnimation { target: pwField; property: "anchors.horizontalCenterOffset";
//                to: -pwFalse.shiftDistance; duration: pwFalse.wobbleTime / 2
//            }
//            //PauseAnimation { duration: 300 }
//            PropertyAnimation { target: pwField; property: "anchors.horizontalCenterOffset";
//                to: pwFalse.shiftDistance; duration: 2 * pwFalse.wobbleTime / 2
//            }
//            //PauseAnimation { duration: 300 }
//            PropertyAnimation { target: pwField; property: "anchors.horizontalCenterOffset";
//                to: 0; duration: pwFalse.wobbleTime / 2
//            }
//        }

        SpringAnimation {
            id: pwFalse

            target: pwField
            property: "anchors.horizontalCenterOffset"

            spring: 20
            damping: 0.1
            from: -50
            to: 0
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
        x: 200
        y: 400
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
