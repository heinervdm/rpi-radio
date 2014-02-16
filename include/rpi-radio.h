#ifndef rpi_radio_H
#define rpi_radio_H

#include <QtGui/QWidget>
#include <QtGui/QGridLayout>

#include "PlayerWidget.h"
#include "ListWidget.h"
#include "Controls.h"

class rpi_radio : public QWidget {
		Q_OBJECT
	public:
		rpi_radio();
		virtual ~rpi_radio();
	private:
		Controls *c;
		PlayerWidget *player;
		ListWidget *list;
		QGridLayout *layout;
	public slots:
		void showList(QStringList entries);
		void listItemSelected(QString station);
};

#endif // rpi_radio_H
