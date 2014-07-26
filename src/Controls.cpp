#include "Controls.h"
#include <QtCore/QtDebug>

Controls::Controls() {
	qDebug("Controls initialized.");
}

Controls::~Controls() {
}

bool Controls::eventFilter (QObject *obj, QEvent *evt) {
	qDebug("eventFilter called.");
	if (evt->type() == QEvent::KeyPress) {
		QKeyEvent *kEvent = static_cast<QKeyEvent *> (evt);
		emit keyEvent(kEvent);
	}
	return QObject::eventFilter (obj, evt);
}
