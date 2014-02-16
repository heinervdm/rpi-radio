#include <QtGui/QApplication>

#include "rpi-radio.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv, QApplication::GuiServer);
	app.setApplicationName("RPiClock");
	PlayerWidget foo;
	foo.show();
	return app.exec();
}
