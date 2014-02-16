#include "rpi-radio.h"
#include "Controls.h"

rpi_radio::rpi_radio() {
	setFixedSize(160, 128);
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);

	player = new PlayerWidget;
	c = new Controls;
	connect(c, SIGNAL(leftEncoderChanged(int)), player, SLOT(volumeChanged(int)));

	layout->addWidget(player, 0, 0);
	installEventFilter(c);
}

rpi_radio::~rpi_radio() {
	player->deleteLater();
	if (layout) delete layout;
	if (c) delete c;
}
