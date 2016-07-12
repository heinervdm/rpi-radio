import QtQuick 1.1

Rectangle {
	id: menuList
	color: "black"
	anchors.fill: parent
	signal entrySelected(string key, string name)
	signal backClicked()

	Component {
		id: menuDelegate
		Item {
			width: parent.width
			height: 40
			Column {
				Text {
					color: "white"
					text: '<b>' + title +'</b><br/>' + subtitle
				}
			}
			MouseArea{
				anchors.fill: parent
				onClicked: {
					menuview.currentIndex = index
					menuList.entrySelected(key, title)
				}
			}
		}
	}

	ListView {
		id: menuview
		width: parent.width
		height: parent.height/4*3-1
		model: menuEntries
		delegate: menuDelegate
		highlight: Rectangle {
			color: "lightsteelblue"
			radius: 5
		}
		focus: true

		Keys.onPressed: {
			if (event.key == Qt.Key_Up) {
				if (menuview.currentIndex > 1) {
					menuview.currentIndex -= 1;
					event.accepted = true;
				}
			}
			else if (event.key == Qt.Key_Down) {
				if (menuview.currentIndex < menuview.count - 1) {
					menuview.currentIndex += 1;
					event.accepted = true;
				}
			}
			else if (event.key == Qt.Key_Return) {
				menuList.entrySelected(menuview.currentItem.key, menuview.currentItem.name)
			}
		}

		Component.onCompleted: {
				menuview.focus = true
				menuview.forceActiveFocus()
		}
	}

	Rectangle {
		id: select
		width: parent.width/2-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.bottom: menuList.bottom
		anchors.left: menuList.left
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
			onClicked: menuList.entrySelected(menuview.currentItem.key, menuview.currentItem.name)
		}
		color: leftMouseArea.pressed || parent.selected == 1 ? "grey" : parent.color
	}
	
	Rectangle {
		id: back
		width: parent.width/2-1
		height: parent.height/4-1
		border.width: 1
		border.color: "white"
		anchors.right: menuList.right
		anchors.bottom: menuList.bottom
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
}
