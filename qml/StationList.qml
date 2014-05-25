import QtQuick 2.0

ListView {
	id: stationList
	z:4
	property bool visibility: false
	anchors.fill: parent
	visible: visibility
	signal selected(string name, string url, string cover)

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
					stationList.selected(name, url, cover)
				}
			}
		}
	}

	model: parent.Stations
	delegate: stationsDelegate
	focus: true
}