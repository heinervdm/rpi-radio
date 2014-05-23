#include "GPIO.h"
#include <QFile>

GPIO::GPIO() {
	exported = false;
	dir = none;
}

GPIO::GPIO(int p) {
	dir = none;
	setPin(p);
}

GPIO::GPIO (int p, GPIO::direction d) {
	setPin(p);
	setDirection(d);
}

void GPIO::setPin (int p) {
	if (exported) unsetPin();
	exported = false;
	pin = p;
	QFile f("/sys/class/gpio/export");
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return;
	f.write(QString::number(pin).toStdString().c_str(), 1);
	f.close();
	exported = true;
}

int GPIO::getPin() {
	return pin;
}

void GPIO::unsetPin () {
	QFile f("/sys/class/gpio/unexport");
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return;
	f.write(QString::number(pin).toStdString().c_str(), 1);
	f.close();
	dir = none;
	exported = false;
}

GPIO::~GPIO() {
	unsetPin();
}

GPIO::level GPIO::read() {
	if (!exported) return unkown;
	QFile f(QString("/sys/class/gpio/gpio%1/value").arg(pin));
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return unkown;
	char res;
	f.read(&res,1);
	f.close();
	if (res=='0') return low;
	else return high;
}

void GPIO::write (GPIO::level l) {
	if (!exported) return;
	QFile f(QString("/sys/class/gpio/gpio%1/value").arg(pin));
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return;
	char c;
	if (l==low) c='0';
	else c='1';
	f.write(&c, 1);
	f.close();
}

void GPIO::setDirection (GPIO::direction d) {
	if (!exported) return;
	QFile f(QString("/sys/class/gpio/gpio%1/direction").arg(pin));
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return;
	QString c;
	if (d==in) {
		c="in\n";
		dir = in;
	}
	else {
		c="out\n";
		dir=out;
	}
	f.write(c.toStdString().c_str(), c.length());
	f.close();
}

GPIO::direction GPIO::getDirection() {
	return dir;
}

void GPIO::setInput() {
	setDirection(in);
}

void GPIO::setOutput() {
	setDirection(out);
}

#define PIN  24 /* P1-18 */
#define POUT 4  /* P1-07 */
