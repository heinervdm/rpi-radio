#include "rpi-radio.h"
#include "rpi-radio.moc"

#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>

#include <QtCore/QTime>
#include <QtCore/QTimer>

rpi_radio::rpi_radio() {
	setBackgroundRole(QPalette::Shadow);
	QHBoxLayout *l = new QHBoxLayout;
	setLayout(l);
	timeLabel = new QLabel;
	timeLabel->setForegroundRole(QPalette::Light);
	l->addWidget(timeLabel, Qt::AlignCenter);
	points = true;
	updateTime();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
	timer->start(1000);
}

rpi_radio::~rpi_radio() {}

void rpi_radio::updateTime() {
	if (points) {
		timeLabel->setText(QTime::currentTime().toString("HH:mm"));
		points = false;
	}
	else {		timeLabel->setText(QTime::currentTime().toString("HH mm"));
		points = true;
	}
	
}
