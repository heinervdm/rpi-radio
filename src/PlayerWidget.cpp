#include "PlayerWidget.h"

#include <QGraphicsItem>
#include <QQmlContext>
#include <QQuickItem>
#include <QNetworkRequest>
#include <QUrl>

#include "StationObject.h"
#include "QmlControl.h"

PlayerWidget::PlayerWidget() {
	qmlRegisterType<QmlControl>("QmlControl", 1, 0, "Control");
	// 	setWindowFlags(Qt::FramelessWindowHint);
	setSource(QUrl("qrc:/qml/Player.qml"));
// 	setWindowState(Qt::WindowFullScreen);
	player = new QMediaPlayer;
	connect(rootObject(), SIGNAL(playClicked()), this, SLOT(playPressed()));
	connect(rootObject(), SIGNAL(stationChanged(QString, QString, QString)), this, SLOT(stationSelected(QString, QString, QString)));
	connect(player, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(mediaDataChanged(QMediaContent)));

	stationList.append(new StationObject("1Live", "http://1live.akacast.akamaistream.net/7/706/119434/v1/gnl.akacast.akamaistream.net/1live", "http://www.einslive.de/codebase/img/content/1Live_Logo.jpg"));
	stationList.append(new StationObject("1Live", "http://1live.akacast.akamaistream.net/7/706/119434/v1/gnl.akacast.akamaistream.net/1live", "http://www.einslive.de/codebase/img/content/1Live_Logo.jpg"));
	stationList.append(new StationObject("1Live", "http://1live.akacast.akamaistream.net/7/706/119434/v1/gnl.akacast.akamaistream.net/1live", "http://www.einslive.de/codebase/img/content/1Live_Logo.jpg"));
	stationList.append(new StationObject("1Live", "http://1live.akacast.akamaistream.net/7/706/119434/v1/gnl.akacast.akamaistream.net/1live", "http://www.einslive.de/codebase/img/content/1Live_Logo.jpg"));
	rootContext()->setContextProperty("stations", QVariant::fromValue(stationList));
}

PlayerWidget::~PlayerWidget() {
}

void PlayerWidget::playPressed() {
	player->play();
}

void PlayerWidget::stationSelected(QString name, QString url, QString cover) {
	QUrl u = QUrl(url);
	QNetworkRequest req = QNetworkRequest(u);
	player->setMedia(u);
}

void PlayerWidget::mediaDataChanged(const QMediaContent& media) {
	
}

void PlayerWidget::volumeChanged(int v) {
	rootObject()->setProperty("volume",QVariant(v));
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
