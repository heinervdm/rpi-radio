import QtQuick 1.0

Rectangle {
	id: background
	z: 5
	anchors.fill: parent
	opacity: 0.5
	color: "grey"
	property int volume: 80
	property bool visibility: false
	visible: visibility
	signal setVolume(int v)
	onSetVolume: {
		background.visibility = true
		volume = v
		offtimer.restart()
	}

	PropertyAnimation {
		target: background
		property: "opacity"
		duration: 400
		from: 0; to: 1
		easing.type: Easing.InOutQuad
		running: true
	}

	Timer {
		id: offtimer
		interval: 1000
		running: false
		repeat: false
		onTriggered: {
			background.visibility = false
		}
	}

	Rectangle {
		id: main
		width: 100
		height: 100
		opacity: 1
		color: "black"
		border.color: "white"
		border.width: 1;
		radius: 10;
		anchors.left: background.left
		anchors.bottom: background.bottom
		anchors.leftMargin: 30
		anchors.bottomMargin: 14

		Rectangle {
			id: rect1
			anchors.leftMargin: 15
			anchors.bottomMargin: 15
			width: 10
			height: 10
			color: {if (background.volume > 0) "green"; else "white"}
			anchors.bottom: main.bottom
			anchors.left: main.left
		}

		Rectangle {
			id: rect2
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 25
			color: {if (background.volume > 20) "green"; else "white"}
			anchors.left: rect1.right
			anchors.bottom: main.bottom
		}

		Rectangle {
			id: rect3
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 40
			color: {if (background.volume > 40) "green"; else "white"}
			anchors.left: rect2.right
			anchors.bottom: main.bottom
		}

		Rectangle {
			id: rect4
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 55
			color: {if (background.volume > 60) "green"; else "white"}
			anchors.left: rect3.right
			anchors.bottom: main.bottom
		}

		Rectangle {
			id: rect5
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 70
			color: {if (background.volume > 80) "green"; else "white"}
			anchors.left: rect4.right
			anchors.bottom: main.bottom
		}
	}
}