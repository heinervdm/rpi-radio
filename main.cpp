#include <QApplication>
#include <QVBoxLayout>

#include "MpdPlayerWidget.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	app.setApplicationName("RPiClock");
	MpdPlayerWidget foo;// = new MpdPlayerWidget;
// 	foo.showFullScreen();
	foo.show();
// 	QWidget *w = new QWidget;
// 	QVBoxLayout *l = new QVBoxLayout;
// 	l->addWidget(foo);
// 	l->setMargin(0);
// 	w->setLayout(l);
// 	w->setMinimumSize(320,240);
// 	w->show();
	return app.exec();
}
