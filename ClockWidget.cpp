#include "ClockWidget.h"
#include "ClockWidget.moc"

#include <QtCore/QTime>
#include <QtCore/QTimer>

#include <QtGui/QGridLayout>

ClockWidget::ClockWidget(QWidget *p) : QWidget(p){
	QGridLayout *l = new QGridLayout;
	setLayout(l);
	timeLabel = new QLabel;
	timeLabel->setStyleSheet("font-size:50px; font-family:Droid Sans Mono;");
	l->addWidget(timeLabel, 0, 0, Qt::AlignCenter);
	dateLabel = new QLabel;
	dateLabel->setStyleSheet("font-size:10px;");
	l->addWidget(dateLabel, 1, 0, Qt::AlignCenter);
	points = true;
	lastDate = new QDate;
	updateTime();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
	timer->start(1000);
}

ClockWidget::~ClockWidget() {
	timeLabel->deleteLater();
	dateLabel->deleteLater();
	delete lastDate;
}

void ClockWidget::updateTime() {
	QDateTime currentTime = QDateTime::currentDateTime();
	if (points) {
		timeLabel->setText(currentTime.toString("HH:mm"));
		points = false;
	}
	else {
		timeLabel->setText(currentTime.toString("HH mm"));
		points = true;
	}
	if (*lastDate != currentTime.date()) {
		dateLabel->setText(currentTime.toString("ddd dd. MMMM yyyy"));
		delete lastDate;
		lastDate = new QDate(currentTime.date());
	}
}

void ClockWidget::mouseReleaseEvent(QMouseEvent* event) {
	emit clicked();
	QWidget::mouseReleaseEvent(event);
}
