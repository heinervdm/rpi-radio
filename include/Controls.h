#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdint.h>

#include <QObject>
#include <QEvent>
#include <QSerialPort>

#include "Button.h"
#include "Encoder.h"

class Controls : public QObject {
		Q_OBJECT
	public:
		Controls(int leftenc = 0, int rightenc = 100);
		~Controls();
	protected:
		bool eventFilter(QObject *obj, QEvent *event);
	private slots:
		void uartEvent();
	private:
		int leftPos;
		int rightPos;
		QSerialPort *serial;
	signals:
		void leftEncoderChanged(int pos);
		void rightEncoderChanged(int pos);
		void leftButtonPressed();
		void rightButtonPressed();
		void middleButtonPressed();
};

#endif // CONTROLS_H
