#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdint.h>

#include <QtCore/QObject>
#include <QtCore/QEvent>

#include "Button.h"
#include "Encoder.h"

class Controls : public QObject {
		Q_OBJECT
	public:
		Controls();
		~Controls();
	protected:
		bool eventFilter (QObject *obj, QEvent *event);
	private slots:
		void leftEncoderChangedSlot (uint8_t pos);
		void rightEncoderChangedSlot (uint8_t pos);
		void leftButtonPressedSlot();
		void rightButtonPressedSlot();
	private:
		Button *leftButton, *rightButton;
		Encoder *leftEncoder, *rightEncoder;
		uint8_t leftPos;
		uint8_t rightPos;
	signals:
		void leftEncoderChanged (uint8_t pos);
		void rightEncoderChanged (uint8_t pos);
		void leftButtonPressed();
		void rightButtonPressed();
};

#endif // CONTROLS_H
