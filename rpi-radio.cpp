#include "rpi-radio.h"
#include "rpi-radio.moc"

rpi_radio::rpi_radio() {
	setFixedSize(160, 128);
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);
	setStyleSheet("margin:0; padding:0; background-color: black; color:white;");

	player = new PlayerWidget;
	clock = new ClockWidget;
	connect(clock,SIGNAL(clicked()),this,SLOT(changeWidget()));

	layout->addWidget(clock, 0, 0);
}

rpi_radio::~rpi_radio() {
	player->deleteLater();
	clock->deleteLater();
	delete layout;
}

void rpi_radio::changeWidget() {
	if (layout->indexOf(clock) > -1) {
		layout->removeWidget(clock);
		layout->addWidget(player,0,0);
	}
	else {
		layout->removeWidget(player);
		layout->addWidget(clock,0,0);
	}
}
