import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
    id: root
    color: "#1d1d1d"

    function pushToOverview() {
        stackView.push("qrc:/Pages/PageStateOverview.qml")
    }

    Component.onCompleted: {
        txtApiToken.text = network.token
        if (txtApiToken.text !== "") {
            pushToOverview()
        }
    }

    Text {
        id: txtTest
        y: 244
        color: "#ffffff"
        text: qsTr("API-Token")
        anchors.bottom: txtApiToken.top
        anchors.bottomMargin: 6
        anchors.left: txtApiToken.left
        anchors.leftMargin: 0
    }

    Image {
        id: banner
        x: 120
        width: 400
        height: 100
        anchors.top: parent.top
        anchors.topMargin: 120
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/img/Telescope 3.jpg"
    }

    TextField {
        id: txtApiToken
        x: 220
        width: 380
        color: "#1d1d1d"
        text: qsTr("")
        font.pointSize: 12
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: banner.bottom
        anchors.topMargin: 43
        selectByMouse: true

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.IBeamCursor
            acceptedButtons: Qt.NoButton
        }
    }

    Button {
        id: button
        x: 270
        text: qsTr("Starten")
        anchors.horizontalCenterOffset: 0
        anchors.top: txtApiToken.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Connections {
        target: button
        onReleased: {
            network.writeToken(txtApiToken.text)
            pushToOverview()
        }
    }
}
