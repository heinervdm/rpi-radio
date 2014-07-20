#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QDeclarativeView>
#include <QUrl>
#include <QString>
#include <QMediaPlayer>
#include <QMediaContent>

class PlayerWidget  : public QDeclarativeView {
		Q_OBJECT

	private:
		QString lastState;
		int lastSelection;
		QMediaPlayer *player;
	public:
		PlayerWidget();
		~PlayerWidget();
	public slots:
		void selectionChanged(int field);
		void select();
	private slots:
		void playPressed();
		void stationSelected(QString name, QString url, QString cover);
		void mediaDataChanged(const QMediaContent & media);
		void volumeChanged(int v);
};

#endif // PLAYERWIDGET_H
