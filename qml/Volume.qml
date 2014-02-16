import QtQuick 1.0

Rectangle {
	id: background
	anchors.fill: parent
	color: "transparent"
	property int volume: 800
	signal setVolume(int v)
	onSetVolume: {
		visible: true
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
		interval: 5000
		running: false
		repeat: false
		onTriggered: {
			background.visible: false
		}
	}
	
	Rectangle {
		id: main
		width: 100
		height: 100
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
			color: {if (background.volume > 200) "green"; else "white"}
			anchors.left: rect1.right
			anchors.bottom: main.bottom
		}

		Rectangle {
			id: rect3
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 40
			color: {if (background.volume > 400) "green"; else "white"}
			anchors.left: rect2.right
			anchors.bottom: main.bottom
		}

		Rectangle {
			id: rect4
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 55
			color: {if (background.volume > 600) "green"; else "white"}
			anchors.left: rect3.right
			anchors.bottom: main.bottom
		}

		Rectangle {
			id: rect5
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 70
			color: {if (background.volume > 800) "green"; else "white"}
			anchors.left: rect4.right
			anchors.bottom: main.bottom
		}
	}
}