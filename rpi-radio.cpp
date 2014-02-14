#include "rpi-radio.h"
#include "rpi-radio.moc"
#include "Controls.h"

rpi_radio::rpi_radio() {
	c = new Controls;
	setFixedSize(160, 128);
	layout = new QGridLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);
	setStyleSheet("margin:0; padding:0; background-color: black; color:white;");

	player = new PlayerWidget;
	connect(player, SIGNAL(showStationSelectList(QStringList)), this, SLOT(showList(QStringList)));
	clock = new ClockWidget;
	connect(clock, SIGNAL(clicked()), this, SLOT(changeWidget()));
	list = new ListWidget;
	connect(list, SIGNAL(selected(QString)), this, SLOT(listItemSelected(QString)));

	layout->addWidget(clock, 0, 0);
	installEventFilter(c);
}

rpi_radio::~rpi_radio() {
	player->deleteLater();
	clock->deleteLater();
	if (layout) delete layout;
	if (c) delete c;
}

void rpi_radio::changeWidget() {
	if (layout->indexOf(clock) > -1) {
		layout->removeWidget(clock);
		layout->addWidget(player, 0, 0);
		player->show();
		clock->hide();
	}
	else {
		layout->removeWidget(player);
		layout->addWidget(clock, 0, 0);
		clock->show();
		player->hide();
	}
}

void rpi_radio::showList(QStringList entries) {
	list->setEntries(entries);
	prevRadio = (layout->indexOf(player) > -1);
	if (prevRadio) {
		layout->removeWidget(player);
		player->hide();
	}
	else {
		layout->removeWidget(clock);
		clock->hide();
	}
	layout->addWidget(list, 0, 0);
	list->show();
}

void rpi_radio::listItemSelected(QString station) {
	qDebug() << "List item selected";
	layout->removeWidget(list);
	if (prevRadio) {
		layout->addWidget(player, 0, 0);
		player->stationSelected(station);
		player->show();
	}
	else {
		layout->addWidget(clock, 0, 0);
		clock->show();
	}
	list->hide();
}
