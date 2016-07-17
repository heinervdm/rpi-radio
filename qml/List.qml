import QtQuick 1.1

Rectangle {
	id: list
	color: "black"
	anchors.fill: parent
	property ListElement currentItem
	signal entrySelected(string key, string name)
	function itemSelected() {
		entrySelected(listview.currentItem.key, listview.currentItem.name)
	}

	Component {
		id: listDelegate
		Rectangle {
			width: parent.width
			height: 40
			Column {
				Text {
					color: {
						if (current) "black"
						else "white"
					}
					text: '<b>' + title +'</b><br/>' + subtitle
				}
			}
			MouseArea{
				anchors.fill: parent
				onClicked: {
					listview.currentIndex = index
					list.entrySelected(key, title)
				}
			}
			color: {
				if (listview.currentIndex == index) "lightsteelblue"
				else if (current) "yellow";
				else "black"
			}
			radius: 5
		}
	}

	ListView {
		id: listview
		width: parent.width
		height: parent.height/4*3-1
		model: listEntries
		delegate: listDelegate
		focus: true

		Keys.onPressed: {
			if (event.key == Qt.Key_Up) {
				if (listview.currentIndex > 1) {
					listview.currentIndex -= 1;
					event.accepted = true;
				}
			}
			else if (event.key == Qt.Key_Down) {
				if (listview.currentIndex < listview.count - 1) {
					listview.currentIndex += 1;
					event.accepted = true;
				}
			}
			else if (event.key == Qt.Key_Return) {
				list.entrySelected(listview.currentItem.key, listview.currentItem.name)
			}
		}

		Component.onCompleted: {
				listview.focus = true
				listview.forceActiveFocus()
		}
	}
}
