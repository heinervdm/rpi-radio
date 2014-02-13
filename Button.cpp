#include "Button.h"
#include <QtCore/QTimer>

Button::Button() {

}

Button::Button (int pin, GPIO::level active) : QObject() {
	init (pin, active);
}

Button::~Button() {
	b->unsetPin();
	if (b) delete b;
}

void Button::init (int pin, GPIO::level active) {
	b = new GPIO (pin, GPIO::in);
	activelevel = active;
	laststate = (activelevel == GPIO::high) ? GPIO::low : GPIO::high;
	QTimer *timer = new QTimer (this);
	connect (timer, SIGNAL (timeout()), this, SLOT (read()));
	timer->start (10);
}

GPIO::level Button::getActiveLevel() {
	return activelevel;
}

int Button::getUsedPin() {
	return b->getPin();
}

void Button::setActiveLevel (GPIO::level l) {
	activelevel = l;
}

void Button::usePin (int pin) {
	b->unsetPin();
	b->setPin(pin);
}

void Button::read() {
	GPIO::level currentstate = b->read();
	if (currentstate == activelevel && laststate != currentstate) {
		emit pressed();
	}
	laststate = currentstate;
}
