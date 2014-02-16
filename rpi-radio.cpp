#include "rpi-radio.h"
#include "Controls.h"

rpi_radio::rpi_radio() {
	setFixedSize(160, 128);
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);
	setStyleSheet("margin:0; padding:0; background-color: black; color:white;");

	player = new PlayerWidget;
	connect(player, SIGNAL(showStationSelectList(QStringList)), this, SLOT(showList(QStringList)));
	list = new ListWidget;
	connect(list, SIGNAL(selected(QString)), this, SLOT(listItemSelected(QString)));
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

void rpi_radio::showList(QStringList entries) {
	list->setEntries(entries);
	layout->removeWidget(player);
	player->hide();
	layout->addWidget(list, 0, 0);
	list->show();
}

void rpi_radio::listItemSelected(QString station) {
	qDebug() << "List item selected";
	layout->removeWidget(list);
	layout->addWidget(player, 0, 0);
	player->stationSelected(station);
	player->show();
	list->hide();
}
