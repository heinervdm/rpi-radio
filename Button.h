#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include "GPIO.h"

class Button : public QObject {
		Q_OBJECT
	public:
		Button();
		Button (int pin, GPIO::level active = GPIO::low);
		~Button();
		void init (int pin, GPIO::level active = GPIO::low);
		void setActiveLevel (GPIO::level l);
		GPIO::level getActiveLevel();
		void usePin (int pin);
		int getUsedPin();
	protected:
		GPIO *b;
		GPIO::level activelevel;
		GPIO::level laststate;
	protected slots:
		void read();
	signals:
		void pressed();
};

#endif // BUTTON_H
