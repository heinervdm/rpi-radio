#include "PlayerWidget.h"

#include <QtGui/QGridLayout>
#include <QtGui/QGraphicsItem>

#include <phonon/MediaSource>

PlayerWidget::PlayerWidget() {
	stationList = new QMap<QString, QString>;
	stationList->insert("SWR3", "http://swr-mp3-m-swr3.akacast.akamaistream.net/7/720/137136/v1/gnl.akacast.akamaistream.net/swr-mp3-m-swr3");
	stationList->insert("RPR1", "http://217.151.151.90:80/stream1");
	stationList->insert("BigFM", "http://srv05.bigstreams.de/bigfm-mp3-96.m3u");

	setSource(QUrl("qrc:/player.qml"));

	connect(rootObject(), SIGNAL(playClicked()), this, SLOT(playPressed()));
	connect(rootObject(), SIGNAL(stationsClicked()), this, SLOT(stationPressed()));

	music = new Phonon::MediaObject(this);
	audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	Phonon::Path path = Phonon::createPath(music, audioOutput);
	connect(music, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
	connect(music, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(musicStateChanged(Phonon::State,Phonon::State)));
}

PlayerWidget::~PlayerWidget() {
	delete stationList;
}

void PlayerWidget::playPressed() {
	qDebug() << "play pressed";
	if (!rootObject()->property("playing").toBool()) {
		music->play();
	}
	else {
		music->stop();
	}
}

void PlayerWidget::stationPressed() {
	emit showStationSelectList(stationList->keys());
}

void PlayerWidget::metaDataChanged() {
	QStringList artist = music->metaData(Phonon::ArtistMetaData);
	QStringList title = music->metaData(Phonon::TitleMetaData);
	if (artist.count() > 0) rootObject()->setProperty("title",QVariant(artist.first()));
	else rootObject()->setProperty("title",QVariant(""));
	if (title.count() > 0) rootObject()->setProperty("subtitle",QVariant(title.first()));
	else rootObject()->setProperty("subtitle",QVariant(""));
}

void PlayerWidget::musicStateChanged(Phonon::State neu, Phonon::State) {
	if (neu == Phonon::StoppedState) {
		rootObject()->setProperty("playing",QVariant(false));
	}
	else if (neu == Phonon::PlayingState) {
		rootObject()->setProperty("playing",QVariant(true));
	}
}

void PlayerWidget::stationSelected(QString station) {
	music->setCurrentSource(Phonon::MediaSource(stationList->value(station)));
	rootObject()->setProperty("name",QVariant(station));
	rootObject()->setProperty("title",QVariant(""));
	rootObject()->setProperty("subtitle",QVariant(""));
}

void PlayerWidget::volumeChanged(int volume) {
	qDebug() << "Changed volume";
	audioOutput->setVolume(1.0 * volume / 1000.0);
}
