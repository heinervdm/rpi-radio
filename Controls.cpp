#include "Controls.h"
#include "Controls.moc"

#include <QKeyEvent>

Controls::Controls() {
	leftPos = 0;
	rightPos = 0;
	leftButton = new Button (1);
	rightButton = new Button (2);
	leftEncoder = new Encoder (3, 4);
	rightEncoder = new Encoder (5, 6);
	connect (leftButton, SIGNAL (pressed()), this, SLOT (leftButtonPressedSlot()));
	connect (rightButton, SIGNAL (pressed()), this, SLOT (rightButtonPressedSlot()));
	connect (leftEncoder, SIGNAL (newPos (int8_t)), this, SLOT (leftEncoderChangedSlot (int8_t)));
	connect (rightEncoder, SIGNAL (newPos (int8_t)), this, SLOT (rightEncoderChangedSlot (int8_t)));
}

Controls::~Controls() {

}

void Controls::leftButtonPressedSlot() {
	emit leftButtonPressed();
}

void Controls::leftEncoderChangedSlot (int8_t pos) {
	leftPos = pos;
	emit leftEncoderChanged (pos);
}

void Controls::rightButtonPressedSlot() {
	emit rightButtonPressed();
}

void Controls::rightEncoderChangedSlot (int8_t pos) {
	rightPos = pos;
	emit rightEncoderChanged (pos);
}

bool Controls::eventFilter (QObject *obj, QEvent *event) {
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent *> (event);
		qDebug ("Ate key press %d", keyEvent->key());
		switch (keyEvent->key()) {
			case Qt::Key_Enter:
				emit rightButtonPressed();
				break;
			case Qt::Key_Control:
				emit leftButtonPressed();
				break;
			case  Qt::Key_Up:
				leftPos++;
				emit leftEncoderChanged(leftPos);
				break;
			case  Qt::Key_Down:
				leftPos--;
				emit leftEncoderChanged(leftPos);
				break;
			case Qt::Key_Plus:
				rightPos++;
				emit rightEncoderChanged(rightPos);
				break;
			case Qt::Key_Minus:
				rightPos--;
				emit rightEncoderChanged(rightPos);
				break;
		}
		return true;
	} else {
		// standard event processing
		return QObject::eventFilter (obj, event);
	}
}
