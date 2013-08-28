#include "ListWidget.h"
#include "ListWidget.moc"

#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>

#include <QtCore/QDebug>

ListWidget::ListWidget(QWidget* parent) : QListWidget(parent) {
	setSelectionMode(QAbstractItemView::SingleSelection);
	setStyleSheet("QListWidgetItem {border:1px solid white;} QListWidgetItem::current:item {color:black; background-color:yellow;}");

	connect(this,SIGNAL(itemSelectionChanged()),this, SLOT(itemSelected()));
}

ListWidget::~ListWidget() {}

void ListWidget::setEntries(QStringList entries) {
	clear();
	for (int i = 0; i < entries.size(); ++i) {
		addItem(entries.at(i));
	}
	setCurrentItem(item(0), QItemSelectionModel::Current);
}

void ListWidget::itemSelected() {
	if (selectedItems().count() == 1) emit selected(selectedItems().at(0)->text());
}
