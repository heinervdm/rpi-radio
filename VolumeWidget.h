/*
 *
 */

#ifndef VOLUMEWIDGET_H
#define VOLUMEWIDGET_H

#include <QtDeclarative/QDeclarativeView>

#include <QtCore/QTimer>

class VolumeWidget : public QDeclarativeView {
		Q_OBJECT
	public:
		VolumeWidget();
		~VolumeWidget();
	public slots:
		void setVolume(int volume);
	private:
		QTimer *timer;
};

#endif // VOLUMEWIDGET_H
