import QtQuick 2.7
import QtQuick.Controls 2.0

Text {
    id: txtAnim
    color: unclickedColor

    property color unclickedColor: "#9D0808"
    property color clickedColor: "#FFF"
    signal clicked()

    PropertyAnimation {
        id: clickAnimClicked
        target: txtAnim
        property: "color"
        to: clickedColor
        duration: 200
    }

    PropertyAnimation {
        id: clickAnimUnclicked
        target: txtAnim
        property: "color"
        to: unclickedColor
        duration: 200
    }


    MouseArea {
        anchors.fill: parent

        onPressed: {
            clickAnimUnclicked.stop()
            clickAnimClicked.start()
        }

        onClicked: {
            txtAnim.clicked()
        }

        onReleased: {
            clickAnimClicked.stop()
            clickAnimUnclicked.start()
        }
    }
}
