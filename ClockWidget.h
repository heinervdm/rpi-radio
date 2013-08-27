#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QMouseEvent>

#include <QtCore/QDate>

class ClockWidget : public QWidget {
		Q_OBJECT
	public:
		ClockWidget(QWidget *parent = 0);
		~ClockWidget();
	protected:
		virtual void mouseReleaseEvent(QMouseEvent * event);
	private:
		QLabel *timeLabel;
		QLabel *dateLabel;
		bool points;
		QDate *lastDate;
	private slots:
		void updateTime();
	signals:
		void clicked();
};

#endif // CLOCKWIDGET_H
