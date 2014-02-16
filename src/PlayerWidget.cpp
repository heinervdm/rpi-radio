#include "PlayerWidget.h"

#include <QtGui/QGraphicsItem>

#include <phonon/MediaSource>

PlayerWidget::PlayerWidget() {
	setSource(QUrl("qrc:/qml/Player.qml"));

	c = new Controls;
	connect(c, SIGNAL(leftEncoderChanged(int)), this, SLOT(volumeChanged(int)));

	connect(rootObject(), SIGNAL(playClicked()), this, SLOT(playPressed()));
	connect(rootObject(), SIGNAL(stationChanged(QString, QString, QString)), this, SLOT(stationSelected(QString,QString,QString)));

	music = new Phonon::MediaObject(this);
	audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	Phonon::Path path = Phonon::createPath(music, audioOutput);
	connect(music, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
	connect(music, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(musicStateChanged(Phonon::State,Phonon::State)));

	installEventFilter(c);
}

PlayerWidget::~PlayerWidget() {
	if (c) delete c;
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

void PlayerWidget::stationSelected(QString station, QString stream, QString playlist) {
	if (playlist.length() > 0) music->setCurrentSource(Phonon::MediaSource(playlist));
	else if (stream.length() > 0) music->setCurrentSource(Phonon::MediaSource(stream));
	else {
		qDebug("Can not play station: No URL given!");
		return;
	}
	rootObject()->setProperty("name",QVariant(station));
	rootObject()->setProperty("title",QVariant(""));
	rootObject()->setProperty("subtitle",QVariant(""));
}

void PlayerWidget::volumeChanged(int volume) {
	qDebug("Changed volume");
	audioOutput->setVolume(1.0 * volume / 1000.0);
}
