#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

#include <QtCore/QMap>

#include <QtDeclarative/QDeclarativeView>

#include <phonon/MediaObject>
#include <phonon/AudioOutput>

class PlayerWidget  : public QDeclarativeView {
		Q_OBJECT
	private:
		QMap<QString, QString> *stationList;
		Phonon::MediaObject *music;
		Phonon::AudioOutput *audioOutput;
	public:
		PlayerWidget();
		~PlayerWidget();
	public slots:
		void stationSelected(QString station);
		void volumeChanged(uint8_t volume);
	private slots:
		void playPressed();
		void stationPressed();
		void metaDataChanged();
		void musicStateChanged(Phonon::State neu, Phonon::State old);
	signals:
		void showStationSelectList(QStringList stations);
};

#endif // PLAYERWIDGET_H
