import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "../Elems"

Rectangle {
    id: root
    color: "#1d1d1d"

    Component.onCompleted: txtToken.text = dbCon.token

    Image {
        z: 1
        id: logo
        x: 132
        width: 376
        height: 100
        anchors.top: parent.top
        anchors.topMargin: 3
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/img/SX Systems.png"

        Text {
            id: tokentext
            color: "#ffffff"
            text: qsTr("Token: ")
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 92
            font.pixelSize: 12
        }

        Text {
            id: txtToken
            color: "#ffffff"
            text: qsTr("")
            anchors.left: tokentext.right
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 92
            font.pixelSize: 12
        }
    }

    Rectangle {
        z: 2
        id: trennstrich
        height: 3
        color: "#1b1717"
        anchors.top: logo.bottom
        anchors.topMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }

    Image {
        z: 99
        id: image
        x: 581
        y: 430
        width: 40
        height: 40
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15

        source: "qrc:/img/ic_add_circle_white_3x.png"
        smooth: true

        MouseArea {
            anchors.fill: parent
            onClicked: {
                print("Add clicked")
                network.test()
            }

        }

    }

    GridView {
        id: lstViewStates

        z: 0
        clip: true

        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: trennstrich.bottom
        anchors.topMargin: 3

        cellHeight: 180
        cellWidth: 300


        model: ListModel {
            ListElement {
                name: "Staat 0"
                alliance: "Allianz 0"
                military: 1234567
                hasAtomicBomb: true
                hasRockets: true
                hasSatellite: true
            }

            ListElement {
                name: "Staat 1"
                alliance: "Allianz 0"
                military: 1234567
                hasAtomicBomb: false
                hasRockets: true
                hasSatellite: false
            }

            ListElement {
                name: "Staat 2"
                alliance: "Allianz 1"
                military: 1234567
                hasAtomicBomb: true
                hasRockets: true
                hasSatellite: false
            }

            ListElement {
                name: "Staat 3"
                alliance: ""
                military: 1234567
                hasAtomicBomb: false
                hasRockets: false
                hasSatellite: false
            }

        }

        delegate: ElemStateOverview {
            txtState: name
            txtAlliance: alliance
            txtMilitary: military.toLocaleString(Qt.locale("de_DE"))
            imgSatelliteVisible: hasSatellite
            imgRocketVisible: hasRockets
            imgAtomicbombVisible: hasAtomicBomb
        }


    }

    Button {
        id: btnChangeToken
        x: 532
        y: 74
        text: qsTr("Change Token")
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: trennstrich.top
        anchors.bottomMargin: 3

        onClicked: stackView.pop();
    }


}
