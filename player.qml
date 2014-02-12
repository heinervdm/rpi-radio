import QtQuick 1.0

Rectangle {
	id: main
	width: 160
	height: 128
	color: "black"
	property bool fav: false
	signal setFavorite(bool f)
	onSetFavorite: fav=f

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
		signal stationsClick()
		MouseArea{
			id: stationsMouseArea
			anchors.fill: parent
			onClicked: stationsClick()
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
		signal playClick()
		MouseArea{
			id: playMouseArea
			anchors.fill: parent
			onClicked: playClick()
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
	}
}
