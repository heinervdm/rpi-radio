import QtQuick 1.0

Item {
	id: main
	width: 320
	height: 240
// 	color: "black"
	state: "CLOCK"
	focus: true

	property int volume: 80
	signal newVolume(int v)
	signal menuItemSelected(string key, string menu)
	signal playStopClicked()
	signal playlistClearClicked()

	onVolumeChanged: {
		 volumeWidget.setVolume(volume)
		 main.newVolume(volume)
// 		 console.log("Volume changed to: "+ volume)
	}

	Volume {
		id: volumeWidget
		anchors.fill: parent
	}

	Keys.onRightPressed: {
		if (volume < 100) {
			volume += 1;
		}
// 		console.log("Right pressed");
	}
	Keys.onLeftPressed: {
		if (volume > 1) {
			volume -= 1;
		}
// 		console.log("Left pressed");
	}

	Loader {
		id: pageLoader
		anchors.fill: parent
	}

	Connections {
		target: pageLoader.item
		ignoreUnknownSignals: true
		onClockClicked: state = "PLAYER"
		onBrowseClicked: state = "MENU"
		onPlayClicked: playStopClicked()
		onBackClicked: state = "PLAYER"
		onPlaylistClicked: state = "PLAYLIST"
		onEntrySelected: menuItemSelected(key, name)
		onClearClicked: playlistClearClicked()
	}

	states: [
		State {
			name: "CLOCK"
			PropertyChanges {
				target: pageLoader
				source: "Clock.qml"
			}
		},
		State {
			name: "PLAYER"
			PropertyChanges {
				target: pageLoader
				source: "MpdPlayer.qml"
			}
		},
		State {
			name: "MENU"
			PropertyChanges {
				target: pageLoader
				source: "Browse.qml"
			}
		},
		State {
			name: "PLAYLIST"
			PropertyChanges {
				target: pageLoader
				source: "Playlist.qml"
			}
		}
	]
}
