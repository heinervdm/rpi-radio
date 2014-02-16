#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QtGui/QListWidget>
#include <QtCore/QStringList>

class ListWidget : public QListWidget {
		Q_OBJECT
	public:
		~ListWidget();
		ListWidget(QWidget* parent = 0);
		void setEntries(QStringList entries);
	private slots:
		void itemSelected();
	signals:
		void selected(QString);
};

#endif // LISTWIDGET_H
