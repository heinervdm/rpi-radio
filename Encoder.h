#ifndef ENCODER_H
#define ENCODER_H

#include "GPIO.h"
#include <stdint.h>
#include <QObject>

class Encoder : public QObject {
		Q_OBJECT
	public:
		Encoder (int pina, int pinb);
		~Encoder();
		int8_t getPos();
	protected:
		void init (int pina, int pinb);
		int8_t enc_delta;
		int8_t last;
		GPIO *pa, *pb;
	private slots:
		void read();
	signals:
		void newPos (int8_t pos);
};

#endif // ENCODER_H
