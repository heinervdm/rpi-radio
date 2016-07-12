#include "MpdPlayerWidget.h"
#include "QMenuListItem.h"

#include <QDeclarativeContext>
#include <QGraphicsObject>
#include <QDebug>

MpdPlayerWidget::MpdPlayerWidget() {
	mpd = &QMpdClient::instance();
	connect(mpd,SIGNAL(initialized()),this, SLOT(onMpdInitialized()));
	connected = mpd->connectToServer("localhost",6600);
	if (!connected) {
		qDebug() << "MpdPlayerWidget:" << "Not connected to MPD!";
	}
	currentPath = "";

	QList<QObject *> menu;
	rootContext()->setContextProperty("menuEntries", QVariant::fromValue(menu));
	rootContext()->setContextProperty("volume", QVariant::fromValue<int>(mpd->status().volume()));
	rootContext()->setContextProperty("playing", QVariant::fromValue<bool>(mpd->status().state() == QMpdStatus::StatePlay));
	rootContext()->setContextProperty("songName", QVariant::fromValue<QString>(mpd->song().title()));
	rootContext()->setContextProperty("songTitle", QVariant::fromValue<QString>(mpd->song().artist()));
	rootContext()->setContextProperty("songSubtitle", QVariant::fromValue<QString>(mpd->song().album()));
	setSource(QUrl("qrc:/qml/main.qml"));
	setAttribute(Qt::WA_NoSystemBackground);
	connect(rootObject(), SIGNAL(newVolume(int)), this, SLOT(setVolume(int)));
	connect(rootObject(), SIGNAL(menuItemSelected(QString, QString)), this, SLOT(onMenuItemSelected(QString,QString)));
	connect(rootObject(), SIGNAL(playStopClicked()), this, SLOT(onPlayStopClicked()));
	qmlState = new QDeclarativeProperty(rootObject(), "state");
	qmlState->connectNotifySignal(this, SLOT(stateChanged()));

	connect(mpd, SIGNAL(songChanged(QMpdSong)), this, SLOT(onSongChanged(QMpdSong)));
	connect(mpd, SIGNAL(stateChanged(QMpdStatus::State)), this, SLOT(onMpdStatusChanged(QMpdStatus::State)));
}

MpdPlayerWidget::~MpdPlayerWidget() {
	mpd->disconnectFromServer();
	mpd->deleteLater();
}

void MpdPlayerWidget::onMpdInitialized() {
	if (!connected) connected = mpd->connectToServer("localhost",6600);
	if (connected) {
		QMpdStatus s = mpd->status();
		switch (s.state()) {
			case QMpdStatus::StatePlay:
				// show player in play mode
				qmlState->write("PLAYER");
				break;
			case QMpdStatus::StatePause:
				// show player in pause mode
				qmlState->write("PLAYER");
				break;
			case QMpdStatus::StateStop:
			default:
				// show time
				qmlState->write("CLOCK");
				break;
		}
	}
}

void MpdPlayerWidget::setVolume(int v) {
	if (!connected) connected = mpd->connectToServer("localhost",6600);
	if (connected) {
		mpd->setVolume(v);
		qDebug() << "MpdPlayerWidget:" << "Volume Changed to "+v;
	}
}

void MpdPlayerWidget::stateChanged() {
	qDebug() << "MpdPlayerWidget:" << "State changed " + qmlState->read().toString();

	if (qmlState->read().toString() == "MENU") {
		currentPath = "root";
		populateMenu();
	}
}

void MpdPlayerWidget::populateMenu() {
	QList<QObject *> menu;
	if (currentPath == "root") {
		menu.append( new QMenuListItem( "Stations", "", "list"));
	} else {
		if (!connected) connected = mpd->connectToServer("localhost",6600);
		if (connected) {
			QMpdEntityList list = mpd->ls(currentPath);
			QMpdSong song;
			QMpdDirectory dir;
			QMpdPlaylist playlist;
			for (int i=0; i<list.length(); i++) {
				switch (list.at(i).getType()) {
					case MPD_ENTITY_TYPE_SONG:
						song = list.at(i).getSong();
						menu.append( new QMenuListItem(song.title(), song.artist()+" ("+song.album()+")", "song:"+song.uri()));
						break;
					case MPD_ENTITY_TYPE_DIRECTORY:
						dir = list.at(i).getDirectory();
						menu.append( new QMenuListItem( dir.getPath(), "", "dir:"+dir.getPath()));
						break;
					case MPD_ENTITY_TYPE_PLAYLIST:
						playlist = list.at(i).getPlaylist();
						menu.append( new QMenuListItem(playlist.getName(), "", "playlist:"+playlist.getName()));
						break;
					default:
						break;
				}
			}
		}
	}
	rootContext()->setContextProperty("menuEntries", QVariant::fromValue(menu));
}

void MpdPlayerWidget::onMenuItemSelected(QString key, QString name) {
	if (!connected) connected = mpd->connectToServer("localhost",6600);
	qDebug() << "MpdPlayerWidget:" << "Menu item clicked";
	if (key.startsWith("list")) {
		currentPath = "";
		populateMenu();
	} else if (key.startsWith("song:")) {
		qDebug() << "MpdPlayerWidget:" << "Song selected";
		qmlState->write("PLAYER");
		if (connected) {
			mpd->addToPlaylist(key.remove(0,5));
			mpd->play();
		}
	} else if (key.startsWith("dir:")) {
		qDebug() << "MpdPlayerWidget:" << "directory selected";
		currentPath = name;
		populateMenu();
	} else if (key.startsWith("playlist:")) {
		qDebug() << "MpdPlayerWidget:" << "Playlist selected";
		qmlState->write("PLAYER");
		if (connected) {
			mpd->loadPlaylist(name);
			mpd->play();
		}
	}
}

void MpdPlayerWidget::onSongChanged(const QMpdSong& song) {
	qDebug() << "MpdPlayerWidget:" << "onSongChanged called";
	rootContext()->setContextProperty("songName", QVariant::fromValue<QString>(song.title()));
	rootContext()->setContextProperty("songTitle", QVariant::fromValue<QString>(song.artist()));
	rootContext()->setContextProperty("songSubtitle", QVariant::fromValue<QString>(song.album()));
}

void MpdPlayerWidget::onMpdStatusChanged(const QMpdStatus::State state) {
	qDebug() << "MpdPlayerWidget:" << "onMpdStatusChanged called";
	if (state == QMpdStatus::StatePlay) {
		rootContext()->setContextProperty("playing", QVariant::fromValue<bool>(true));
	} else if (state == QMpdStatus::StateStop) {
		rootContext()->setContextProperty("playing", QVariant::fromValue<bool>(false));
	} else if (state == QMpdStatus::StatePause) {
		rootContext()->setContextProperty("playing", QVariant::fromValue<bool>(false));
	} else {
	}
}

void MpdPlayerWidget::onPlayStopClicked() {
	if (!connected) connected = mpd->connectToServer("localhost",6600);
	if (connected) {
		if (mpd->status().state() == QMpdStatus::StatePlay) {
			qDebug() << "MpdPlayerWidget:" << "Stop";
			mpd->stop();
		} else {
			qDebug() << "MpdPlayerWidget:" << "Play";
			mpd->play();
		}
	}
}
