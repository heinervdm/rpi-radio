#ifndef CONTROLS_H
#define CONTROLS_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>

class Controls : public QObject {
		Q_OBJECT
	public:
		Controls();
		~Controls();
	protected:
		bool eventFilter(QObject *obj, QEvent *event);
	signals:
		void keyEvent(QKeyEvent *event);
};

#endif // CONTROLS_H
