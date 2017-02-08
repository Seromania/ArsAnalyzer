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
    property alias txtFieldAlliance: txtFieldAlliance.text
    property alias txtMilitary: txtMilitary.text
    property alias txtMuster: txtMuster.text

    property int stateid: -1

    readonly property int trennWidth: 1
    readonly property int topBottomMargin: 5
    readonly property int leftRightMargin: 3

    signal deleteStateClicked(int stateid)

    width: 300
    height: 180

    function changeEditAlliance() {
        if (txtAlliance.visible === true) {
            txtEditAlliance.text = "Speichern"
            txtAlliance.visible = false
            txtFieldAlliance.enabled = true
            txtFieldAlliance.visible = true
        } else {
            txtEditAlliance.text = "Editieren"
            txtAlliance.visible = true
            txtFieldAlliance.enabled = false
            txtFieldAlliance.visible = false

            countryModel.updateCountriesAlliance(stateid, txtFieldAlliance.text)
        }
    }

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

    AnimText {
        id: txtEditAlliance
        text: qsTr("Editieren")
        anchors.left: txtState.right
        anchors.leftMargin: 12
        anchors.bottom: txtState.bottom
        wrapMode: Text.WordWrap
        font.pixelSize: 12

        onClicked: {
            changeEditAlliance()
        }
    }

    AnimText {
        id: txtDeleteCountry
        text: qsTr("Löschen")
        anchors.left: txtEditAlliance.right
        anchors.leftMargin: 8
        anchors.bottom: txtEditAlliance.bottom
        anchors.bottomMargin: 0
        wrapMode: Text.WordWrap
        font.pixelSize: 12

        onClicked: {
            deleteStateClicked(stateid)
        }
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

    TextField {
        id: txtFieldAlliance
        color: "#000"
        text: qStr("Bündnis 0")
        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.top: txtState.bottom
        anchors.topMargin: 8
        wrapMode: Text.WordWrap
        enabled: false
        visible: false
        selectByMouse: true
        font.pointSize: 12
        maximumLength: 12
        placeholderText: "Allianz"

        Keys.onReturnPressed: {
            changeEditAlliance()
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            cursorShape: Qt.IBeamCursor
        }
    }

    Text {
        id: txtMilitaryText
        color: "#ffffff"
        text: qsTr("Militär:")
        anchors.top: txtFieldAlliance.bottom
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

    Text {
        id: txtMuster
        color: "#ffffff"
        text: qsTr("Staatsmuster")
        anchors.left: txtState.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        font.pixelSize: 16
    }
}
