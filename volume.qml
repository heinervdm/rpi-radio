import QtQuick 1.0

Rectangle {
	id: background
	width: 160
	height: 128
	color: "transparent"

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
		property int volume: 100
		signal setVolume(int v)
		onSetVolume: volume = v

		Rectangle {
			id: rect1
			anchors.leftMargin: 15
			anchors.bottomMargin: 15
			width: 10
			height: 10
			color: {if (parent.volume > 0) "green"; else "white"}
			anchors.bottom: main.bottom
			anchors.left: main.left
		}
		
		Rectangle {
			id: rect2
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 25
			color: {if (parent.volume > 20) "green"; else "white"}
			anchors.left: rect1.right
			anchors.bottom: main.bottom
		}

		Rectangle {
			id: rect3
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 40
			color: {if (parent.volume > 40) "green"; else "white"}
			anchors.left: rect2.right
			anchors.bottom: main.bottom
		}

		Rectangle {
			id: rect4
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 55
			color: {if (parent.volume > 60) "green"; else "white"}
			anchors.left: rect3.right
			anchors.bottom: main.bottom
		}

		Rectangle {
			id: rect5
			anchors.leftMargin:5
			anchors.bottomMargin: 15
			width: 10
			height: 70
			color: {if (parent.volume > 80) "green"; else "white"}
			anchors.left: rect4.right
			anchors.bottom: main.bottom
		}
	}
}