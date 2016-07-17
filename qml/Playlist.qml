import QtQuick 1.1

Rectangle {
	color: "black"
	anchors.fill: parent
	signal entrySelected(string key, string name)
	signal backClicked()

	List {
		id: playlist
	}

	Rectangle {
		id: select
		width: parent.width/2-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.bottom: playlist.bottom
		anchors.left: playlist.left
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
		Text {
			font.pixelSize: parent.height * 0.55
			anchors.centerIn: parent
			color: "white"
			text: "Select"
		}
		MouseArea{
			id: leftMouseArea
			anchors.fill: parent
			onClicked: playlist.itemSelected()
		}
		color: leftMouseArea.pressed || parent.selected == 1 ? "grey" : parent.color
	}
	
	Rectangle {
		id: back
		width: parent.width/2-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.right: playlist.right
		anchors.bottom: playlist.bottom
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
		Text {
			font.pixelSize: parent.height * 0.55
			anchors.centerIn: parent
			color: "white"
			text: "Back"
		}
		MouseArea{
			id: rightMouseArea
			anchors.fill: parent
			onClicked: backClicked()
		}
		color: rightMouseArea.pressed || parent.selected == 2 ? "grey" : parent.color
	}

	Component.onCompleted: {
		playlist.entrySelected.connect(entrySelected)
	}
}
