#include "ClockWidget.h"

#include <QtGui/QGraphicsItem>

ClockWidget::ClockWidget() {
	setSource(QUrl("qrc:/clock.qml"));

	connect(rootObject(), SIGNAL(clicked()), this, SLOT(clockClicked()));
}

ClockWidget::~ClockWidget() {
}

void ClockWidget::clockClicked() {
	emit clicked();
}
