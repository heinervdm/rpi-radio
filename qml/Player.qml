import QtQuick 2.0
import QtMultimedia 5.0

Rectangle {
	id: player
	implicitWidth: 320
	implicitHeight: 240
// 	anchors.fill: parent
	color: "black"
	state: "CLOCK"
	property bool fav: false
	property bool playing: false
	property string name: ""
	property string title: ""
	property string subtitle: ""
	property int selected: 0 // 0=none, 1=stations, 2=play, 3=favorite
	property int volume: 80
	signal favoriteClicked()
	signal playClicked()
	signal stationsClicked()
	signal stationChanged(string name, string url, string cover)

	onStationsClicked: {
		player.state = "STATIONLIST"
	}
	onStationChanged: {
		console.log("Station selected: " + name)
		player.state = "PLAYER"
		player.name = name
	}
	onVolumeChanged: {
		 volumeWidget.setVolume(volume)
		 console.log("Volume changed to: "+ volume)
		 playMusic.volume = volume/100.0
	}
	function nextStation() {
		stationlist.incrementCurrentIndex()
	}
	function prevStation() {
		stationlist.decrementCurrentIndex()
	}
	function click() {
		if (player.state == "PLAYER") {
			switch (player.selected) {
				case 1: stationsClicked(); break
				case 2: playClicked(); break
				case 3: favoriteClicked(); break
			}
		} else if (player.state == "STATIONLIST") {
			stationChanged(stationlist.model.get(stationlist.currentIndex).name, stationlist.model.get(stationlist.currentIndex).url, stationlist.model.get(stationlist.currentIndex).cover)
		} else if (player.state == "CLOCK") {
			player.state = "PLAYER"
		}
	}

	Volume {
		id: volumeWidget
	}

	Clock {
		id: clock
		onClockClicked: {
			player.state = "PLAYER"
		}
	}

	StationList {
		id: stationlist
		onSelected: {
			player.stationChanged(name, url, cover)
		}
	}

	Text {
		id: stationname
		font.pixelSize: parent.height * 0.2
		scale: paintedWidth > width ? (width / paintedWidth) : 1
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
		scale: paintedWidth > width ? (width / paintedWidth) : 1
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
		scale: paintedWidth > width ? (width / paintedWidth) : 1
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
		anchors.bottom: player.bottom
		anchors.left: player.left
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
			onClicked: player.stationsClicked()
		}
		color: stationsMouseArea.pressed || parent.selected == 1 ? "grey" : parent.color
	}
	
	Rectangle {
		id: play
		width: parent.width/2-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.right: player.right
		anchors.bottom: player.bottom
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
		Text {
			font.pixelSize: parent.height * 0.55
			anchors.centerIn: parent
			color: "white"
			text: (player.playing) ? "Stop" : "Play"
		}
		MouseArea{
			id: playMouseArea
			anchors.fill: parent
			onClicked: player.playClicked()
		}
		color: playMouseArea.pressed || parent.selected == 2 ? "grey" : parent.color
	}

	Rectangle {
		id: star
		z:2
		anchors.rightMargin:5
		anchors.topMargin: 5
		width: 15
		height: 15
		radius: width*0.5
		border.width: 1
		border.color: parent.selected ==3 ? "red" : "yellow"
		color: fav ? "yellow" : "transparent"
		anchors.right: player.right
		anchors.top: player.top
		opacity: 0.5
		MouseArea{
			id: favoriteMouseArea
			anchors.fill: parent
			onClicked: {
				fav = !fav
				player.favoriteClicked()
			}
		}
	}

	states: [
		State {
			name: "CLOCK"
			PropertyChanges {
				target: clock
				visibility: true
			}
			PropertyChanges {
				target:	stationlist
				visibility: false
			}
		},
		State {
			name: "PLAYER"
			PropertyChanges {
				target: clock
				visibility: false
			}
			PropertyChanges {
				target:	stationlist
				visibility: false
			}
		},
		State {
			name: "STATIONLIST"
			PropertyChanges {
				target: clock
				visibility: false
			}
			PropertyChanges {
				target:	stationlist
				visibility: true
			}
		}
	]
}
