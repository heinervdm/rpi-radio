#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QtDeclarative/QDeclarativeView>

#include <phonon/MediaObject>
#include <phonon/AudioOutput>

class PlayerWidget  : public QDeclarativeView {
		Q_OBJECT
	private:
		Phonon::MediaObject *music;
		Phonon::AudioOutput *audioOutput;
	public:
		PlayerWidget();
		~PlayerWidget();
	public slots:
		void stationSelected(QString station, QString stream, QString playlist);
		void volumeChanged(int volume);
	private slots:
		void playPressed();
		void metaDataChanged();
		void musicStateChanged(Phonon::State neu, Phonon::State old);
};

#endif // PLAYERWIDGET_H
