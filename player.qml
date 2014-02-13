import QtQuick 1.0

Rectangle {
	id: main
	width: 160
	height: 128
	color: "black"
	property bool fav: false
	signal favoriteClicked()
	signal playClicked()
	signal stationsClicked()

	Rectangle {
		id: stations
		width: parent.width/2
		height: parent.height/4
		border.width: 1
		border.color: "white"
		anchors.bottom: main.bottom
		anchors.left: main.left
		Text {
			font.pixelSize: parent.height * 0.55
			anchors.centerIn: parent
			color: "white"
			text: "Stations"
		}
		MouseArea{
			id: stationsMouseArea
			anchors.fill: parent
			onClicked: parent.stationsClicked()
		}
		color: stationsMouseArea.pressed ? "grey" : parent.color
	}
	
	Rectangle {
		id: play
		width: parent.width/2
		height: parent.height/4
		border.width: 1
		border.color: "white"
		anchors.right: main.right
		anchors.bottom: main.bottom
		Text {
			font.pixelSize: parent.height * 0.55
			anchors.centerIn: parent
			color: "white"
			text: "Play"
		}
		MouseArea{
			id: playMouseArea
			anchors.fill: parent
			onClicked: parent.playClicked()
		}
		color: playMouseArea.pressed ? "grey" : parent.color
	}

	Rectangle {
		id: star
		anchors.rightMargin:5
		anchors.topMargin: 5
		width: 20
		height: 20
		radius: width*0.5
		border.width: 1
		border.color: "yellow"
		color: fav ? "yellow" : "transparent"
		anchors.right: main.right
		anchors.top: main.top
		MouseArea{
			id: favoriteMouseArea
			anchors.fill: parent
			onClicked: {
				fav = !fav
				parent.favoriteClicked()
			}
		}
	}
}
