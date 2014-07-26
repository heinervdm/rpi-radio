import QtQuick 1.0
// import StationModel 1.0

Rectangle {
	id: stationList
	z:4
	width: 320
	height: 240
	property bool visibility: true
// 	property StationModel stations;
	property alias stations: coverFlow.listModel
	property alias currentName: coverFlow.name
	property alias currentUrl: coverFlow.url
	property alias currentCover: coverFlow.cover

	visible: visibility
	signal selected(string name, string url, string cover)

	function incrementCurrentIndex() {
		console.log("incrementCurrentIndex")
		coverFlow.incrementCurrentIndex()
	}

	function decrementCurrentIndex() {
		console.log("decrementCurrentIndex")
		coverFlow.decrementCurrentIndex()
	}

	Text {
		id: myText
		anchors.bottom: parent.bottom
		text: "current"
		anchors.horizontalCenter: parent.horizontalCenter
	}

	CoverFlow {
		id: coverFlow

		width: parent.width
		height: parent.height
		anchors.top: parent.top
		anchors.bottom: myText.top

// 		listModel: stations

		onIndexChanged: {
// 			if (stations == NULL) console.log("stations NULL")
			myText.text = name
		}

		onItemSelected: {
			selected(name, url, cover)
			console.log("clicked")
		}

		itemWidth: 120
		itemHeight: 120

		color: "black"

	}

	Component.onCompleted: {
		myText.text = coverFlow.name
	}
}
