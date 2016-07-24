import QtQuick 1.1

Rectangle {
	id: list
	color: "black"
	anchors.fill: parent
	property string currentKey
	property string currentTitle
	signal entrySelected(string key, string name)
	signal itemClicked()
	function getSelectedItem() {
		entrySelected(currentKey, currentTitle)
	}

	Component {
		id: listDelegate
		Rectangle {
			id: wrapper
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
					console.log("Selecting index: " + index +", key: "+key+", title: "+title)
					listview.currentIndex = index
					currentKey = key
					currentTitle = title
					console.log("Selecting index: " + listview.currentIndex +", key: "+listview.currentItem.key+", title: "+listview.currentItem.title)
					itemClicked()
// 					list.entrySelected(key, title)
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
				currentKey = listview.currentItem.key
				currentTitle = listview.currentItem.title
				list.itemClicked()
// 				list.entrySelected(listview.currentItem.key, listview.currentItem.name)
			}
		}

		Component.onCompleted: {
				listview.focus = true
				listview.forceActiveFocus()
		}
	}
}
