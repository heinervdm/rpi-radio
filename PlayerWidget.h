#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

#include <QtCore/QMap>

#include <phonon/MediaObject>

class PlayerWidget : public QWidget {
		Q_OBJECT
	private:
		QMap<QString, QString> *stationList;
		QLabel *artistLabel;
		QLabel *trackLabel;
		QLabel *stationLabel;
		QPushButton *playButton;
		QPushButton *changeStationButton;
		Phonon::MediaObject *music;
	public:
		PlayerWidget();
		~PlayerWidget();
	private slots:
		void playPressed();
		void stationPressed();
		void metaDataChanged();
		void musicStateChanged(Phonon::State neu,Phonon::State old);
};

#endif // PLAYERWIDGET_H
