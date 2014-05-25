import QtQuick 2.0

Rectangle {
	id: main
	z: 10
	anchors.fill: parent
	color: "black"
	property bool visibility: true
	visible: visibility
	signal clockClicked()

	Timer {
		property bool dots: true
		interval: 1000
		running: true
		repeat: true
		onTriggered: {
			if (dots) {
				time.text = Qt.formatDateTime(new Date(), "HH:mm")
			} else {
				time.text = Qt.formatDateTime(new Date(), "HH mm")
			}
			date.text = Qt.formatDateTime(new Date(), "ddd dd. MMMM yyyy")
			dots = !dots;
		}
	}
	Text { 
		id: time
		font.pixelSize: parent.height * 0.4
		font.family: "Droid Sans Mono"
		width: parent.width
		height: parent.height * 2.0 / 3.0
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		anchors.top: parent.top
		anchors.left: parent.left
		color: "white"
	}
	Text {
		id: date
		font.pixelSize: parent.height * 0.1
		width: parent.width
		height: parent.height / 3.0
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		anchors.top: time.bottom
		anchors.left: parent.left
		color: "white"
	}
	MouseArea{
		id: clockMouseArea
		anchors.fill: parent
		onClicked: parent.clockClicked()
	}
}
