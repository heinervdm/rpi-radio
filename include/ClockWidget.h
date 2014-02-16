#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QtCore/QObject>

#include <QtDeclarative/QDeclarativeView>

class ClockWidget : public QDeclarativeView {
		Q_OBJECT
	public:
		ClockWidget();
		~ClockWidget();
	protected slots:
		void clockClicked();
	signals:
		void clicked();
};

#endif // CLOCKWIDGET_H
