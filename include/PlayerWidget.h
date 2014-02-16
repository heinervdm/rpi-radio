#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QtDeclarative/QDeclarativeView>

#include <phonon/MediaObject>
#include <phonon/AudioOutput>

#include "Controls.h"

class PlayerWidget  : public QDeclarativeView {
		Q_OBJECT
	private:
		Controls *c;
		Phonon::MediaObject *music;
		Phonon::AudioOutput *audioOutput;
	public:
		PlayerWidget();
		~PlayerWidget();
	public slots:
		void stationSelected(QString station, QString stream, QString playlist);
		void volumeChanged(int volume);
		void selectionChanged(int field);
		void select();
	private slots:
		void playPressed();
		void metaDataChanged();
		void musicStateChanged(Phonon::State neu, Phonon::State old);
};

#endif // PLAYERWIDGET_H
