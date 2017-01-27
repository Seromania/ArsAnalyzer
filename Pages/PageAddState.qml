import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
    id: root
    color: "#1d1d1d"

    Image {
        id: btnBack
        y: 8
        width: 25
        height: 25
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: text3.verticalCenter
        source: "qrc:/img/ic_arrow_back_white_24dp_1x.png"

        MouseArea {
            width: 30
            height: 30
            anchors.fill: parent

            onClicked: stackView.pop()
        }
    }

    TextField {
        id: txtStateID
        width: 380
        color: "#1d1d1d"
        text: qsTr("")
        anchors.verticalCenterOffset: -30
        anchors.horizontalCenterOffset: 0
        font.pointSize: 12
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        selectByMouse: true
        inputMethodHints: Qt.ImhFormattedNumbersOnly
        maximumLength: 6
        placeholderText: "Staatsid"

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.IBeamCursor
            acceptedButtons: Qt.NoButton
        }
    }

    Text {
        id: text1
        y: 210
        color: "#ffffff"
        text: qsTr("Staatsid")
        anchors.left: txtStateID.left
        anchors.leftMargin: 0
        anchors.bottom: txtStateID.top
        anchors.bottomMargin: 3
        font.pixelSize: 12
    }

    TextField {
        id: txtAlliance
        width: 380
        color: "#1d1d1d"
        text: qsTr("")
        anchors.left: txtStateID.left
        anchors.leftMargin: 0
        anchors.top: txtStateID.bottom
        anchors.topMargin: 40
        selectByMouse: true
        font.pointSize: 12
        placeholderText: "Allianz"

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            cursorShape: Qt.IBeamCursor
        }
    }

    Text {
        id: text2
        x: -9
        y: 214
        color: "#ffffff"
        text: qsTr("Allianz")
        anchors.leftMargin: 0
        anchors.bottom: txtAlliance.top
        anchors.left: txtAlliance.left
        font.pixelSize: 12
        anchors.bottomMargin: 0
    }

    Button {
        id: btnAdd
        x: 270
        text: qsTr("Hinzufügen")
        anchors.top: txtAlliance.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: txtAlliance.horizontalCenter

        onClicked: {
            indicatorBusy.running = true
            var cid = parseInt(txtStateID.text)
            if (isInteger(cid)) {
                if (cid.toString().length === 6) {
                    print("Müsste eine ID sein!")
                    askBeforeAccept(cid)
                } else {
                    indicatorBusy.running = false
                    print("Keine ID!")
                }
            } else {
                indicatorBusy.running = true
                print("Keine ID!")
            }
            print("ID: " + cid)
        }
    }

    Text {
        id: text3
        x: -7
        color: "#ffffff"
        text: qsTr("Staat hinzufügen")
        anchors.horizontalCenterOffset: 0
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 36
    }

    Image {
        id: image
        x: 159
        width: 330
        height: 100
        anchors.top: text3.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/img/Telescope 3.jpg"
    }

    function isInteger(n) {
        return n === +n && n === (n|0);
    }

    function askBeforeAccept(id) {
        network.getNameFor(id)
    }

    BusyIndicator {
        anchors.centerIn: parent.Center
        id: indicatorBusy
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        running: false

    }

    Popup {
        id: popup

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        focus: true
        modal: false

        property string stateName: ""

        ColumnLayout {
            spacing: 5
            Text {
                font.pixelSize: 14
                anchors.horizontalCenter: parent.horizontalCenter
                text: popup.stateName + " hinzufügen?"
            }

            RowLayout {
                Button {
                    text: "Ja"
                }
                Button {
                    text: "Abbrechen"
                    onClicked: popup.close()
                }
            }


        }
    }

    Connections {
        target: network
        onGotName: {
            indicatorBusy.running = false
            print("Got Name: " + name)
            popup.stateName = name
            popup.open()
        }
    }
}
