#ifndef ENCODER_H
#define ENCODER_H

#include "GPIO.h"
#include <QtCore/QObject>

class Encoder : public QObject {
		Q_OBJECT
	public:
		Encoder (int pina, int pinb, int pos = 0);
		~Encoder();
	public slots:
		int getPos();
		void setPos(int pos);
	protected:
		void init (int pina, int pinb, int pos = 0);
		char enc_delta;
		char last;
		GPIO *pa, *pb;
		int currentPos;
	private slots:
		void read();
		void read2();
	signals:
		void newPos (int pos);
};

#endif // ENCODER_H
