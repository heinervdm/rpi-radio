import QtQuick 2.0
import QmlControl 1.0

Rectangle {
	id: coverFlow

	property int itemWidth: 100
	property int itemHeight: 100

	property ListModel listModel

	signal indexChanged(int index)
	signal itemSelected(int index)

	function incrementCurrentIndex() {
		myPathView.incrementCurrentIndex()
	}

	function decrementCurrentIndex() {
		myPathView.decrementCurrentIndex()
	}

	Component {
		id: appDelegate

		Rectangle {
			id: myFlipable
			property double angle: PathView.angle

			width: itemWidth; height: itemHeight
			z: PathView.z
			scale: PathView.iconScale

			function itemClicked() {
				if (myPathView.currentIndex == index) {
					PathView.view.currentIndex = index
					PathView.view.click()
				}
				else {
					PathView.view.currentIndex = index
				}
			}

			MouseArea {
				anchors.fill: parent
				onClicked: itemClicked()
			}
			transform: Rotation {
				id: rotation
				origin.x: myFlipable.width/2
				origin.y: myFlipable.height/2
				axis.x: 0; axis.y: 1; axis.z: 0
				angle: myFlipable.angle
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

		signal itemClicked()
		signal click()

		onClick: {
			itemClicked()
		}

		anchors.fill: parent
		pathItemCount: 10
		preferredHighlightBegin: 0.5
		preferredHighlightEnd: 0.5
		focus: true
		interactive: true
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
			indexChanged(myPathView.currentIndex);
		})
		myPathView.itemClicked.connect(function(){
			itemSelected(myPathView.currentIndex);
		})
	}
}
