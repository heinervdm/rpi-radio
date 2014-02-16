import QtQuick 1.0
import "qml"

Rectangle {
	id: main
	width: 160
	height: 128
	color: "black"
	property bool fav: false
	property bool playing: false
	property bool playSelected: false
	property bool stationsSelected: false
	property string name: ""
	property string title: ""
	property string subtitle: ""
	signal favoriteClicked()
	signal playClicked()
	signal stationsClicked()
	signal volumeChanged(int v)
	signal stationChanged(string name, string stream, string playlist)
	onStationChanged: {
		console.log("Station selected: " +name)
	}
	onVolumeChanged: {
		 volume.setVolume(v)
		 console.log("Volume changed to: "+ v)
	}

	Volume {
		id: volume
	}

	Clock {
		id: clock
	}

	StationList {
		id: stationlist
		onSelected: main.stationChanged(name, stream, playlist)
	}

	Text {
		id: stationname
		font.pixelSize: parent.height * 0.2
		width: parent.width
		height: (parent.height - stations.height) / 3.0
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		anchors.top: parent.top
		anchors.left: parent.left
		color: "white"
		text: parent.name
	}
	Text {
		id: stationtitle
		font.pixelSize: parent.height * 0.1
		width: parent.width
		height: (parent.height - stations.height) / 3.0
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		anchors.top: stationname.bottom
		anchors.left: parent.left
		color: "white"
		text: parent.title
	}
	Text {
		id: stationsubtitle
		font.pixelSize: parent.height * 0.1
		width: parent.width
		height: (parent.height - stations.height) / 3.0
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		anchors.top: stationtitle.bottom
		anchors.left: parent.left
		color: "white"
		text: parent.subtitle
	}

	Rectangle {
		id: stations
		width: parent.width/2-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.bottom: main.bottom
		anchors.left: main.left
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
		Text {
			font.pixelSize: parent.height * 0.55
			anchors.centerIn: parent
			color: "white"
			text: "Stations"
		}
		MouseArea{
			id: stationsMouseArea
			anchors.fill: parent
			onClicked: stationlist.visibility = true
		}
		color: stationsMouseArea.pressed || parent.stationsSelected ? "grey" : parent.color
	}
	
	Rectangle {
		id: play
		width: parent.width/2-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.right: main.right
		anchors.bottom: main.bottom
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
		Text {
			font.pixelSize: parent.height * 0.55
			anchors.centerIn: parent
			color: "white"
			text: (main.playing) ? "Stop" : "Play"
		}
		MouseArea{
			id: playMouseArea
			anchors.fill: parent
			onClicked: main.playClicked()
		}
		color: playMouseArea.pressed || parent.playSelected ? "grey" : parent.color
	}

	Rectangle {
		id: star
		anchors.rightMargin:5
		anchors.topMargin: 5
		width: 15
		height: 15
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
				main.favoriteClicked()
			}
		}
	}
}
