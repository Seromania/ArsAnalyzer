import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "../Elems"

Rectangle {
    id: root
    color: "#1d1d1d"

    Component.onCompleted: txtToken.text = network.token

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
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        source: "qrc:/img/ic_add_circle_white_3x.png"
        smooth: true

        MouseArea {
            anchors.fill: parent
            onClicked: {
                stackView.push("qrc:/Pages/PageAddState.qml")
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


        model: countryModel

        delegate: ElemStateOverview {
            txtState: model.name
            txtAlliance: (model.alliance === "") ? "Keine Allianz" : model.alliance
            txtFieldAlliance: model.alliance
            txtMilitary: model.military.toLocaleString(Qt.locale("de_DE"))
            imgSatelliteVisible: model.hasSatellite
            imgRocketVisible: model.hasRocket
            imgAtomicbombVisible: model.hasAtomic
            stateid: model.id
            txtMuster: model.muster
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
