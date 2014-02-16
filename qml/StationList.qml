import QtQuick 1.0

ListView {
	id: stationList
	z:4
	property bool visibility: false
	anchors.fill: parent
	visible: visibility
	signal selected(string name, string stream, string playlist)
	onSelected: visibility = false

	Component {
		id: stationsDelegate
		Rectangle {
			id: wrapper
			width:  stationList.width
			height: stationInfo.height
			color: ListView.isCurrentItem ? "grey" : "black"
			Text {
				id: stationInfo
				text: name
				color: "white"
			}
			MouseArea {
				id: stationMouseArea
				anchors.fill: parent
				onPressed: {
					stationList.selected(name, stream, playlist)
				}
			}
		}
	}

	model: Stations {}
	delegate: stationsDelegate
	focus: true
}