#include <QtGui/QApplication>

#include "PlayerWidget.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	app.setApplicationName("RPiClock");
	PlayerWidget foo;
	foo.showFullScreen();
	return app.exec();
}
