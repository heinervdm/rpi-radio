#ifndef rpi_radio_H
#define rpi_radio_H

#include <QtGui/QWidget>
#include <QtGui/QGridLayout>

#include "ClockWidget.h"
#include "PlayerWidget.h"
#include "ListWidget.h"

class rpi_radio : public QWidget {
		Q_OBJECT
	public:
		rpi_radio();
		virtual ~rpi_radio();
	private:
		ClockWidget *clock;
		PlayerWidget *player;
		ListWidget *list;
		QGridLayout *layout;
		bool prevRadio;
	public slots:
		void changeWidget();
		void showList(QStringList entries);
		void listItemSelected(QString station);
};

#endif // rpi_radio_H
