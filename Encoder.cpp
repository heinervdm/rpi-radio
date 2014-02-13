#include "Encoder.h"
#include "Encoder.moc"

#include <QtCore/QTimer>

Encoder::Encoder(int pina, int pinb) : QObject() {
	init(pina, pinb);
}

Encoder::~Encoder() {
	delete pa;
	delete pb;
}

void Encoder::init(int pina, int pinb) {
	pa = new GPIO(pina, GPIO::in);
	pb = new GPIO(pinb, GPIO::in);

	int8_t newstate;

	newstate = 0;
	if( pa->read() == GPIO::high )
		newstate = 3;
	if( pb->read() == GPIO::high )
		newstate ^= 1;                              // convert gray to binary
	last = newstate;                                // power on state
	enc_delta = 0;
	
	 QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(read()));
     timer->start(10);
}

void Encoder::read() {
	int8_t newstate, diff;

	newstate = 0;
	if( pa->read() == GPIO::high )
		newstate = 3;
	if( pb->read() == GPIO::high )
		newstate ^= 1;                      // convert gray to binary
	diff = last - newstate;                 // difference last - new
	if( diff & 1 ){                    // bit 0 = value (1)
		last = newstate;                    // store new as next last
		enc_delta += (diff & 2) - 1;   // bit 1 = direction (+/-)
	}
	if ((diff & 2) - 1 != 0) emit newPos(getPos());
}

int8_t Encoder::getPos() {
	int8_t val;

	val = enc_delta;
	enc_delta = val & 1;
	return val >> 1;
}
