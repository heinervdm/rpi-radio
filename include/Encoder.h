#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>

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
		int currentPos;
		int lPina, lPinb;
	private slots:
		void read();
		void read2();
	signals:
		void newPos (int pos);
};

#endif // ENCODER_H
