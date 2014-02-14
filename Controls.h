#ifndef CONTROLS_H
#define CONTROLS_H

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
		void leftEncoderChangedSlot (int8_t pos);
		void rightEncoderChangedSlot (int8_t pos);
		void leftButtonPressedSlot();
		void rightButtonPressedSlot();
	private:
		Button *leftButton, *rightButton;
		Encoder *leftEncoder, *rightEncoder;
		int8_t leftPos, rightPos;
	signals:
		void leftEncoderChanged (int pos);
		void rightEncoderChanged (int pos);
		void leftButtonPressed();
		void rightButtonPressed();
};

#endif // CONTROLS_H
