import QtQuick 2.0

Rectangle {
	id: stationList
	z:4
	implicitWidth: 320
	implicitHeight: 240
	property bool visibility: false
	property ListModel stations;

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

	CoverFlow {
		id: coverFlow
		listModel: stationList.stations

		width: parent.width
		anchors.top: parent.top
		anchors.bottom: myText.top

		onIndexChanged: {
			myText.text = listModel.get(index).name
		}
		
		onItemSelected: {
			selected(listModel.get(index).name, listModel.get(index).url, listModel.get(index).cover)
		}

		itemWidth: 120
		itemHeight: 120

		color: "black"
	}
}
