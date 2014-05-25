#include "Controls.h"

#include <QKeyEvent>
#include <QDebug>

Controls::Controls(int leftenc, int rightenc) {
	leftPos = leftenc;
	rightPos = rightenc;
	serial = new QSerialPort("/dev/ttyACM0");
	serial->open(QSerialPort::ReadOnly);
	connect(serial, SIGNAL(readyRead()), this, SLOT(uartEvent()));
}

Controls::~Controls() {
	serial->deleteLater();
}

bool Controls::eventFilter (QObject *obj, QEvent *evt) {
	if (evt->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent *> (evt);
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
				return QObject::eventFilter (obj, evt);
		}
		return true;
	} else {
		// standard event processing
		return QObject::eventFilter (obj, evt);
	}
}

void Controls::uartEvent() {
	QByteArray data = serial->readAll();
	qDebug("UART: " + data);
	if (data.startsWith("Encoder L:")) {
		emit leftEncoderChanged(data.split(':').at(1).toInt());
	} else if (data.startsWith("Encoder R:")) {
		int v = data.split(':').at(1).toInt();
		v = (v > 100) ? 100 : v;
		emit rightEncoderChanged(v);
	} else if (data.startsWith("Button Pressed: L")) {
		emit leftButtonPressed();
	} else if (data.startsWith("Button Pressed: M")) {
	} else if (data.startsWith("Button Pressed: R")) {
		emit rightButtonPressed();
	}  
}
