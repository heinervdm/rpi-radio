import QtQuick 1.0

Rectangle {
	id: coverFlow

	property int itemWidth: 100
	property int itemHeight: 100

	property alias listModel: myPathView.model
// 	property alias currentIndex: myPathView.currentIndex

	property int index;
	property string name;
	property string url;
	property string cover;

	signal indexChanged(int index, string name)
	signal itemSelected(string name, string url, string cover)

	function incrementCurrentIndex() {
		console.log("incrementCurrentIndex 2")
		myPathView.incrementCurrentIndex()
	}

	function decrementCurrentIndex() {
		console.log("decrementCurrentIndex 2")
		myPathView.decrementCurrentIndex()
	}

	Component {
		id: appDelegate

		Flipable {
			id: myFlipable

			property bool flipped: false

			width: itemWidth; height: itemHeight
			z: PathView.z
			scale: PathView.iconScale

			function itemClicked() {
				if (myPathView.currentIndex == index) {
					myPathView.click()
				}
				else {
					myPathView.currentIndex = index
				}
			}

			Binding {
				target: coverFlow;
				property: "name";
				value: name;
				when: myPathView.currentIndex == index
			}

			Binding {
				target: coverFlow;
				property: "index";
				value: index;
				when: myPathView.currentIndex == index
			}

			Binding {
				target: coverFlow;
				property: "url";
				value: url;
				when: myPathView.currentIndex == index
			}

			Binding {
				target: coverFlow;
				property: "cover";
				value: cover;
				when: myPathView.currentIndex == index
			}

			MouseArea {
				anchors.fill: parent
				onClicked: itemClicked()
			}

			Rectangle {
				smooth: true
				width: itemWidth; height: itemHeight
				anchors.horizontalCenter: parent.horizontalCenter
				anchors.verticalCenter: parent.verticalCenter
				color: "black"
				border.color: "white"
				border.width: 3

				Image {
					id: myIcon
					anchors.centerIn: parent
					fillMode: Image.PreserveAspectFit
					width: parent.width*0.9
					height: parent.height*0.9
					source: cover
					smooth: true
				}
			}
		}
	}

	PathView {
		id: myPathView

		signal stationSelected()

 		function click() {
			stationSelected()
		}

		onIncrementCurrentIndex: console.log("index incrementet")
		onDecrementCurrentIndex: console.log("index decrementet")

		anchors.fill: parent
		preferredHighlightBegin: 0.5
		preferredHighlightEnd: 0.5
		focus: true
		pathItemCount: 10
		model: listModel
		delegate: appDelegate
		path: Path {
			startX: 0
			startY: coverFlow.height / 2
			PathAttribute { name: "z"; value: 0 }
			PathAttribute { name: "angle"; value: 60 }
			PathAttribute { name: "iconScale"; value: 0.5 }
			PathLine { x: coverFlow.width / 2; y: coverFlow.height / 2;  }
			PathAttribute { name: "z"; value: 100 }
			PathAttribute { name: "angle"; value: 0 }
			PathAttribute { name: "iconScale"; value: 1.0 }
			PathLine { x: coverFlow.width; y: coverFlow.height / 2; }
			PathAttribute { name: "z"; value: 0 }
			PathAttribute { name: "angle"; value: -60 }
			PathAttribute { name: "iconScale"; value: 0.5 }
		}
	}

	Component.onCompleted: {
		myPathView.currentIndexChanged.connect(function(){
			indexChanged(index, name);
		})
		myPathView.stationSelected.connect(function(){
			itemSelected(name, url, cover);
		})
	}
}
