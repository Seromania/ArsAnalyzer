import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
    color: "#1d1d1d"
    property alias imgSatelliteVisible: imgSatellite.visible
    property alias imgRocketVisible: imgRocket.visible
    property alias imgAtomicbombVisible: imgAtomicbomb.visible
    property alias txtState: txtState.text
    property alias txtAlliance: txtAlliance.text
    property alias txtMilitary: txtMilitary.text

    readonly property int trennWidth: 1
    readonly property int topBottomMargin: 5
    readonly property int leftRightMargin: 3

    width: 300
    height: 180

    Rectangle {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        width: trennWidth
        color: "#ffffff"
        anchors.leftMargin: leftRightMargin
        anchors.bottomMargin: topBottomMargin
        anchors.topMargin: topBottomMargin
    }

    Rectangle {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        width: trennWidth
        color: "#ffffff"
        anchors.rightMargin: leftRightMargin
        anchors.bottomMargin: topBottomMargin
        anchors.topMargin: topBottomMargin
    }

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: trennWidth
        color: "#ffffff"

        anchors.rightMargin: leftRightMargin
        anchors.leftMargin: leftRightMargin
        anchors.bottomMargin: topBottomMargin
        anchors.topMargin: topBottomMargin
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        height: trennWidth
        color: "#ffffff"

        anchors.rightMargin: leftRightMargin
        anchors.leftMargin: leftRightMargin
        anchors.bottomMargin: topBottomMargin
        anchors.topMargin: topBottomMargin
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent;
        onClicked: print("Meine Farbe: " + parent.color)

        Text {
            id: txtState
            color: "#ffffff"
            text: qsTr("Staat 0")
            anchors.left: parent.left
            anchors.leftMargin: 12
            anchors.top: parent.top
            anchors.topMargin: 12
            wrapMode: Text.WordWrap
            font.pixelSize: 16
        }

        Text {
            id: txtAlliance
            color: "#ffffff"
            text: qsTr("Bündnis 0")
            anchors.left: parent.left
            anchors.leftMargin: 12
            anchors.top: txtState.bottom
            anchors.topMargin: 8
            wrapMode: Text.WordWrap
            font.pixelSize: 16
        }

        Text {
            id: txtMilitaryText
            color: "#ffffff"
            text: qsTr("Militär:")
            anchors.top: txtAlliance.bottom
            anchors.topMargin: 12
            anchors.left: txtState.left
            anchors.leftMargin: 0
            font.pixelSize: 16
        }

        Text {
            id: txtMilitary
            color: "#ffffff"
            text: qsTr("1.234.567")
            anchors.left: txtMilitaryText.right
            anchors.leftMargin: 30
            anchors.top: txtMilitaryText.top
            anchors.topMargin: 0
            font.pixelSize: 16
        }

        Image {
            id: imgAtomicbomb
            x: 247
            width: 45
            height: 45
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
            source: "qrc:/img/atomic.png"
        }

        Image {
            id: imgRocket
            x: 247
            width: 45
            height: 45
            anchors.top: imgAtomicbomb.bottom
            anchors.topMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
            source: "qrc:/img/rocket.png"
        }

        Image {
            id: imgSatellite
            x: 247
            width: 45
            height: 45
            anchors.top: imgRocket.bottom
            anchors.topMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
            source: "qrc:/img/satelite.png"
        }
    }
}
