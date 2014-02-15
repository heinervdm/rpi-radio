#include "Encoder.h"
#include "Encoder.moc"

#include <QtCore/QTimer>

Encoder::Encoder (int pina, int pinb, int pos) : QObject() {
	init (pina, pinb);
}

Encoder::~Encoder() {
	delete pa;
	delete pb;
}

void Encoder::init (int pina, int pinb, int pos) {
	pa = new GPIO (pina, GPIO::in);
	pb = new GPIO (pinb, GPIO::in);

	char newstate;

	newstate = 0;

	if (pa->read() == GPIO::high)
		newstate = 3;

	if (pb->read() == GPIO::high)
		newstate ^= 1;                              // convert gray to binary

	last = newstate;                                // power on state
	enc_delta = pos;

	QTimer *timer = new QTimer (this);
	connect (timer, SIGNAL (timeout()), this, SLOT (read()));
	timer->start (10);
	QTimer *timer2 = new QTimer (this);
	connect (timer2, SIGNAL (timeout()), this, SLOT (getPos()));
	timer2->start (100);
}

void Encoder::read() {
	char newstate, diff;

	newstate = 0;

	if (pa->read() == GPIO::high)
		newstate = 3;

	if (pb->read() == GPIO::high)
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
	if ((val >> 1) != 0) emit newPos(currentPos);
}

void Encoder::setPos(int pos) {
	currentPos = pos;
}

int Encoder::getPos() {
	return currentPos;
}
