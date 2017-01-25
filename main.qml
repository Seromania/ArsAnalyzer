import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "Pages/"

ApplicationWindow {
    id: applicationWindow
    visible: true
    minimumWidth: 640
    minimumHeight: 480
    width: 640
    height: 480
    color: "#1d1d1d"
    title: qsTr("ArsAnalyzer")

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: PageStart {}
    }
}
