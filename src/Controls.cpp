#include "Controls.h"

#include <QKeyEvent>

Controls::Controls(int leftenc, int rightenc) {
	leftPos = leftenc;
	rightPos = rightenc;
	leftButton = new Button (1);
	rightButton = new Button (2);
	leftEncoder = new Encoder (3, 4, leftPos);
	rightEncoder = new Encoder (5, 6, rightPos);
	connect (leftButton, SIGNAL (pressed()), this, SLOT (leftButtonPressedSlot()));
	connect (rightButton, SIGNAL (pressed()), this, SLOT (rightButtonPressedSlot()));
	connect (leftEncoder, SIGNAL (newPos (int)), this, SLOT (leftEncoderChangedSlot (int)));
	connect (rightEncoder, SIGNAL (newPos (int)), this, SLOT (rightEncoderChangedSlot (int)));
}

Controls::~Controls() {

}

void Controls::setLeftEncoderPositon(int pos) {
	leftPos = pos;
}

void Controls::setRightEncoderPosition(int pos) {
	rightPos = pos;
}

void Controls::leftButtonPressedSlot() {
	emit leftButtonPressed();
}

void Controls::leftEncoderChangedSlot (int pos) {
	leftPos = pos;
	emit leftEncoderChanged (pos);
}

void Controls::rightButtonPressedSlot() {
	emit rightButtonPressed();
}

void Controls::rightEncoderChangedSlot (int pos) {
	if (pos > 100) rightEncoder->setPos(100);
	if (pos < 0) rightEncoder->setPos(0);
	if (rightPos != pos) emit rightEncoderChanged (pos);
	rightPos = pos;
}

bool Controls::eventFilter (QObject *obj, QEvent *event) {
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent *> (event);
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
				if (rightPos < 100) rightPos++;
				emit rightEncoderChanged(rightPos);
				break;
			case Qt::Key_Minus:
				if (rightPos > 0) rightPos--;
				emit rightEncoderChanged(rightPos);
				break;
			default:
				qDebug ("Unused key %d", keyEvent->key());
				return QObject::eventFilter (obj, event);
		}
		return true;
	} else {
		// standard event processing
		return QObject::eventFilter (obj, event);
	}
}
