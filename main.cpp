#include <QtGui/QApplication>
#include "rpi-radio.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    rpi_radio foo;
    foo.show();
    return app.exec();
}
