#include "VolumeWidget.h"

#include <QtCore/QUrl>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include <QtGui/QGraphicsItem>

VolumeWidget::VolumeWidget() {
	setSource(QUrl("qrc:/volume.qml"));
	setStyleSheet(QString("background: transparent"));
	timer = new QTimer;
	connect(timer, SIGNAL(timeout()), this, SLOT(hide()));
}

VolumeWidget::~VolumeWidget() {

}

void VolumeWidget::setVolume(int volume) {
	rootObject()->setProperty("volume",QVariant(volume));
	raise();
	show();
	timer->setSingleShot(true);
	timer->start(5000);
}
