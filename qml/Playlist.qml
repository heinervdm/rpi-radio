import QtQuick 1.1

Rectangle {
	color: "black"
	anchors.fill: parent
	signal entrySelected(string key, string name)
	signal backClicked()
	signal clearClicked()

	List {
		id: playlist
	}

	Rectangle {
		id: select
		width: parent.width/3-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.bottom: playlist.bottom
		anchors.left: playlist.left
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
		Image {
			sourceSize.height: parent.height*0.55
			fillMode: Image.PreserveAspectFit
			anchors.centerIn: parent
			source: "qrc:/icons/plus-round.svg"
		}
		MouseArea{
			id: leftMouseArea
			anchors.fill: parent
			onClicked: playlist.getSelectedItem()
		}
		color: leftMouseArea.pressed || parent.selected == 1 ? "grey" : parent.color
	}

	Rectangle {
		id: clear
		width: parent.width/3-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.horizontalCenter: playlist.horizontalCenter
		anchors.bottom: playlist.bottom
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
		Image {
			sourceSize.height: parent.height*0.55
			fillMode: Image.PreserveAspectFit
			anchors.centerIn: parent
			source: "qrc:/icons/trash-a.svg"
		}
		MouseArea{
			id: clearMouseArea
			anchors.fill: parent
			onClicked: clearClicked()
		}
		color: clearMouseArea.pressed || parent.selected == 2 ? "grey" : parent.color
	}

	Rectangle {
		id: back
		width: parent.width/3-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.right: playlist.right
		anchors.bottom: playlist.bottom
		anchors.leftMargin: border.width
		anchors.bottomMargin: border.width
		Image {
			sourceSize.height: parent.height*0.55
			fillMode: Image.PreserveAspectFit
			anchors.centerIn: parent
			source: "qrc:/icons/arrow-left-a.svg"
		}
		MouseArea{
			id: rightMouseArea
			anchors.fill: parent
			onClicked: backClicked()
		}
		color: rightMouseArea.pressed || parent.selected == 3 ? "grey" : parent.color
	}

	Component.onCompleted: {
		playlist.entrySelected.connect(entrySelected)
	}
}
