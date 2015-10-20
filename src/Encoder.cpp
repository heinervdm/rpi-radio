#include "Encoder.h"
#include "PJ_RPI.h"

#include <QTimer>

Encoder::Encoder (int pina, int pinb, int pos) : QObject() {
	init (pina, pinb, pos);
}

Encoder::~Encoder() {
}

void Encoder::init (int pina, int pinb, int pos) {
	lPina = pina;
	lPinb = pinb;
	INP_GPIO(lPina);
	INP_GPIO(lPinb);

	char newstate;

	newstate = 0;

	if (GPIO_READ(lPina))
		newstate = 3;

	if (GPIO_READ(lPinb))
		newstate ^= 1;                              // convert gray to binary

	last = newstate;                                // power on state
	currentPos = pos;

	QTimer *timer = new QTimer (this);
	connect (timer, SIGNAL (timeout()), this, SLOT (read()));
	timer->start (1);
	QTimer *timer2 = new QTimer (this);
	connect (timer2, SIGNAL (timeout()), this, SLOT (getPos()));
	timer2->start (100);
}

void Encoder::read() {
	char newstate, diff;

	newstate = 0;

	if (GPIO_READ(lPina))
		newstate = 3;

	if (GPIO_READ(lPinb))
		newstate ^= 1;                      // convert gray to binary

	diff = last - newstate;                 // difference last - new

	if (diff & 1) {                    // bit 0 = value (1)
		last = newstate;                    // store new as next last
		enc_delta += (diff & 2) - 1;   // bit 1 = direction (+/-)
	}
}

void Encoder::read2() {
	char val;

	val = enc_delta;
	enc_delta = val & 1;
	currentPos += val >> 1;
	if ((val >> 1) != 0) {
		emit newPos(currentPos);
// 		QKeyEvent *event;
// 		if (enc_delta > 0) event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
// 		else event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
// 		QCoreApplication::postEvent (receiver, event);
	}
}

void Encoder::setPos(int pos) {
	currentPos = pos;
}

int Encoder::getPos() {
	return currentPos;
}
