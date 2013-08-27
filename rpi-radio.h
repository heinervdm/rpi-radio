#ifndef rpi_radio_H
#define rpi_radio_H

#include <QtGui/QWidget>
#include <QtGui/QGridLayout>

#include "ClockWidget.h"
#include "PlayerWidget.h"

class rpi_radio : public QWidget {
		Q_OBJECT
	public:
		rpi_radio();
		virtual ~rpi_radio();
	private:
		ClockWidget *clock;
		PlayerWidget *player;
		QGridLayout *layout;
	public slots:
		void changeWidget();
};

#endif // rpi_radio_H
