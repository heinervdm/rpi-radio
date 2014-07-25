#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include "config.h"

#include <QDeclarativeView>
#include <QUrl>
#include <QString>
#ifdef HAVE_QT5
#include <QMediaPlayer>
#include <QMediaContent>
#elif HAVE_QT5
#include <phonon/MediaObject>
#include <phonon/AudioOutput>
#endif

class PlayerWidget  : public QDeclarativeView {
		Q_OBJECT

	private:
		QString lastState;
		int lastSelection;
#ifdef HAVE_QT5
		QMediaPlayer *player;
#elif HAVE_QT5
		Phonon::MediaObject *music;
		Phonon::AudioOutput *audioOutput;
#endif

	public:
		PlayerWidget();
		~PlayerWidget();
	public slots:
		void selectionChanged(int field);
		void select();
	private slots:
		void playPressed();
		void stationSelected(QString name, QString url, QString cover);
#ifdef HAVE_QT5
		void mediaDataChanged(const QMediaContent & media);
#elif HAVE_QT5
		void metaDataChanged();
		void musicStateChanged(Phonon::State neu, Phonon::State old);
#endif
		void volumeChanged(int v);
};

#endif // PLAYERWIDGET_H
