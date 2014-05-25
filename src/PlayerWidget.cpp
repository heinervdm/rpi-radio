#include "PlayerWidget.h"

#include <QGraphicsItem>
#include <QQmlContext>
#include <QQuickItem>

#include "StationObject.h"

PlayerWidget::PlayerWidget() {
// 	setWindowFlags(Qt::FramelessWindowHint);
	setSource(QUrl("qrc:/qml/Player.qml"));
// 	setWindowState(Qt::WindowFullScreen);

	c = new Controls(0,80);
	connect(c, SIGNAL(rightEncoderChanged(int)), this, SLOT(volumeChanged(int)));
	connect(c, SIGNAL(leftEncoderChanged(int)), this, SLOT(selectionChanged(int)));
	connect(c, SIGNAL(leftButtonPressed()), this, SLOT(select()));
	connect(c, SIGNAL(rightButtonPressed()), this, SLOT(select()));
	connect(rootObject(), SIGNAL(playClicked()), this, SLOT(playPressed()));
	connect(rootObject(), SIGNAL(stationChanged(QString, QString, QString)), this, SLOT(stationSelected(QString, QString, QString)));

	stationList.append(new StationObject("1Live", "http://1live.akacast.akamaistream.net/7/706/119434/v1/gnl.akacast.akamaistream.net/1live", ""));
	rootContext()->setContextProperty("Stations", QVariant::fromValue(stationList));

	installEventFilter(c);
}

PlayerWidget::~PlayerWidget() {
	if (c) delete c;
}

void PlayerWidget::selectionChanged(int field) {
	QString state = rootObject()->property("state").toString();
	if (state == "PLAYER") {
		rootObject()->setProperty("selected", QVariant((field % 4 + 4) % 4));
	} else if (state == "CLOCK") {
		rootObject()->setProperty("state", QVariant("PLAYER"));
	} else if (state == "STATIONLIST") {
		if (field > lastSelection) {
			QVariant returnedValue;
			QMetaObject::invokeMethod(rootObject(), "prevStation", Q_RETURN_ARG(QVariant, returnedValue));
		} else if (field < lastSelection) {
			QVariant returnedValue;
			QMetaObject::invokeMethod(rootObject(), "nextStation", Q_RETURN_ARG(QVariant, returnedValue));
		}
	} else {
		qDebug("Application in unknown state!");
	}
	lastState = state;
	lastSelection = field;
}

void PlayerWidget::select() {
	QVariant returnedValue;
	QMetaObject::invokeMethod(rootObject(), "click", Q_RETURN_ARG(QVariant, returnedValue));
}
