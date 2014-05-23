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
	public slots:
		void setLeftEncoderPositon(int pos);
		void setRightEncoderPosition(int pos);
	protected:
		bool eventFilter(QObject *obj, QEvent *event);
	private slots:
		void leftEncoderChangedSlot(int pos);
		void rightEncoderChangedSlot(int pos);
		void leftButtonPressedSlot();
		void rightButtonPressedSlot();
		void uartEvent();
	private:
		Button *leftButton, *rightButton;
		Encoder *leftEncoder, *rightEncoder;
		int leftPos;
		int rightPos;
		QSerialPort *serial;
	signals:
		void leftEncoderChanged(int pos);
		void rightEncoderChanged(int pos);
		void leftButtonPressed();
		void rightButtonPressed();
};

#endif // CONTROLS_H
