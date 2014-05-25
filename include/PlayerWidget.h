#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QQuickView>
#include <QUrl>
#include <QString>

#include "Controls.h"
#include "StationObject.h"

class PlayerWidget  : public QQuickView {
		Q_OBJECT

	private:
		Controls *c;
		QString lastState;
		int lastSelection;
		QList<QObject*> stationList;
	public:
		PlayerWidget();
		~PlayerWidget();
	public slots:
		void selectionChanged(int field);
		void select();
	private slots:
};

#endif // PLAYERWIDGET_H
