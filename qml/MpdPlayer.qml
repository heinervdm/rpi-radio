import QtQuick 1.1

Rectangle {
	id: player
	color: "black"

// 	property bool playing: false
// 	property string songName: ""
// 	property string songTitle: ""
// 	property string songSubtitle: ""

	signal playClicked()
	signal browseClicked()
	signal playlistClicked()

	Text {
		id: stationname
		font.pixelSize: parent.height * 0.2
		scale: paintedWidth > width ? (width / paintedWidth) : 1
		width: parent.width
		height: (parent.height - menu.height) / 3.0
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		anchors.top: parent.top
		anchors.left: parent.left
		color: "white"
		text: songName
	}

	Text {
		id: stationtitle
		font.pixelSize: parent.height * 0.1
		scale: paintedWidth > width ? (width / paintedWidth) : 1
		width: parent.width
		height: (parent.height - menu.height) / 3.0
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		anchors.top: stationname.bottom
		anchors.left: parent.left
		color: "white"
		text: songTitle
	}

	Text {
		id: stationsubtitle
		font.pixelSize: parent.height * 0.1
		scale: paintedWidth > width ? (width / paintedWidth) : 1
		width: parent.width
		height: (parent.height - menu.height) / 3.0
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		anchors.top: stationtitle.bottom
		anchors.left: parent.left
		color: "white"
		text: songSubtitle
	}

	Rectangle {
		id: menu
		width: parent.width/3-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.bottom: player.bottom
		anchors.left: player.left
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
// 		Text {
// 			font.pixelSize: parent.height * 0.55
// 			anchors.centerIn: parent
// 			color: "white"
// 			text: "Browse"
// 		}
		Image {
			sourceSize.height: parent.height*0.55
			fillMode: Image.PreserveAspectFit
			anchors.centerIn: parent
			source: "qrc:/icons/browse.svg"
		}
		MouseArea{
			id: menuMouseArea
			anchors.fill: parent
			onClicked: player.browseClicked()
		}
		color: menuMouseArea.pressed || parent.selected == 1 ? "grey" : parent.color
	}
	
	Rectangle {
		id: play
		width: parent.width/3-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.right: playlist.left
		anchors.bottom: player.bottom
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
// 		Text {
// 			font.pixelSize: parent.height * 0.55
// 			anchors.centerIn: parent
// 			color: "white"
// 			text: (playing) ? "Stop" : "Play"
// 		}
		Image {
			sourceSize.height: parent.height*0.55
			fillMode: Image.PreserveAspectFit
			anchors.centerIn: parent
			source: (playing) ? "qrc:/icons/pause.svg" : "qrc:/icons/play.svg"
		}
		MouseArea{
			id: playMouseArea
			anchors.fill: parent
			onClicked: player.playClicked()
		}
		color: playMouseArea.pressed || parent.selected == 2 ? "grey" : parent.color
	}

	Rectangle {
		id: playlist
		width: parent.width/3-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.right: player.right
		anchors.bottom: player.bottom
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
// 		Text {
// 			font.pixelSize: parent.height * 0.55
// 			anchors.centerIn: parent
// 			color: "white"
// 			text: "Playlist"
// 		}
		Image {
			sourceSize.height: parent.height*0.55
			fillMode: Image.PreserveAspectFit
			anchors.centerIn: parent
			source: "qrc:/icons/list.svg"
		}
		MouseArea{
			id: playlistMouseArea
			anchors.fill: parent
			onClicked: player.playlistClicked()
		}
		color: playlistMouseArea.pressed || parent.selected == 2 ? "grey" : parent.color
	}
}
