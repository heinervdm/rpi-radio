#ifndef rpi_radio_H
#define rpi_radio_H

#include <QtGui/QWidget>
#include <QtGui/QLabel>

class rpi_radio : public QWidget
{
Q_OBJECT
public:
    rpi_radio();
    virtual ~rpi_radio();
private:
	QLabel *timeLabel;
	bool points;
private slots:
	void updateTime();
};

#endif // rpi_radio_H
