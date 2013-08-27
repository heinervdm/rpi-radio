#include "PlayerWidget.h"
#include "PlayerWidget.moc"

#include <QtGui/QGridLayout>

#include <phonon/MediaSource>
#include <phonon/AudioOutput>

PlayerWidget::PlayerWidget() {
	stationList = new QMap<QString, QString>;
	stationList->insert("SWR3", "http://swr-mp3-m-swr3.akacast.akamaistream.net/7/720/137136/v1/gnl.akacast.akamaistream.net/swr-mp3-m-swr3");

	QGridLayout *l = new QGridLayout;
	setLayout(l);
	stationLabel = new QLabel;
	l->addWidget(stationLabel, 0, 0, 1, 2, Qt::AlignHCenter);
	trackLabel = new QLabel;
	l->addWidget(trackLabel, 1, 0, 1, 2, Qt::AlignHCenter);
	artistLabel = new QLabel;
	l->addWidget(artistLabel, 2, 0, 1, 3, Qt::AlignHCenter);
	playButton = new QPushButton("Play");
	connect(playButton, SIGNAL(pressed()), this, SLOT(playPressed()));
	l->addWidget(playButton, 3, 1);
	changeStationButton = new QPushButton("Stations");
	connect(changeStationButton, SIGNAL(pressed()), this, SLOT(stationPressed()));
	l->addWidget(changeStationButton, 3, 0);

	music = new Phonon::MediaObject(this);
	Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	Phonon::Path path = Phonon::createPath(music, audioOutput);
	connect(music, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
	connect(music, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(musicStateChanged(Phonon::State,Phonon::State)));
}

PlayerWidget::~PlayerWidget() {
	stationLabel->deleteLater();
	trackLabel->deleteLater();
	artistLabel->deleteLater();
	playButton->deleteLater();
	changeStationButton->deleteLater();
	delete stationList;
}

void PlayerWidget::playPressed() {
	if (playButton->text().startsWith("Play")) {
		music->setCurrentSource(Phonon::MediaSource(stationList->value("SWR3")));
		stationLabel->setText("SWR3");
		music->play();
	}
	else {
		music->stop();
	}
}

void PlayerWidget::stationPressed() {
	
}

void PlayerWidget::metaDataChanged() {
	QStringList artist = music->metaData(Phonon::ArtistMetaData);
	QStringList title = music->metaData(Phonon::TitleMetaData);
	if (artist.count() > 0) artistLabel->setText(artist.first());
	else artistLabel->setText("");
	if (title.count() > 0) trackLabel->setText(title.first());
	else trackLabel->setText("");
}

void PlayerWidget::musicStateChanged(Phonon::State neu, Phonon::State) {
	if (neu == Phonon::StoppedState) {
		playButton->setText("Play");
	}
	else if (neu == Phonon::PlayingState) {
		playButton->setText("Stop");
	}
}
