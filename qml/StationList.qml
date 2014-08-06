import QtQuick 1.1

Rectangle {
	id: stationList
	z:4
	width: 320
	height: 240
	property bool visibility: true
	property alias stations: coverFlow.listModel
	property alias currentName: coverFlow.name
	property alias currentUrl: coverFlow.url
	property alias currentCover: coverFlow.cover

	visible: visibility
	signal selected(string name, string url, string cover)

	function incrementCurrentIndex() {
		coverFlow.incrementCurrentIndex()
	}

	function decrementCurrentIndex() {
		coverFlow.decrementCurrentIndex()
	}

	Text {
		id: myText
		anchors.bottom: parent.bottom
		text: "current"
		anchors.horizontalCenter: parent.horizontalCenter
	}

	Binding {
		target: myText;
		property: "text";
		value: coverFlow.name;
		when: true
	}

	CoverFlow {
		id: coverFlow

		width: parent.width
		height: parent.height
		anchors.top: parent.top
		anchors.bottom: myText.top

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
