#include <QHeaderView>
#include "tablewidget.h"

TableWidget::TableWidget(QWidget* parent) :
	QTableWidget(parent) {

}

TableWidget::TableWidget(int rowCount, int columnCount, QWidget *parent) :
	TableWidget(parent) {

	// set the columns and rows of the table
	this->setColumnCount(columnCount);
	this->setRowCount(rowCount);

	// make the table ajust to the parent widget
	for (int c = 0; c < this->horizontalHeader()->count(); ++c) {
		this->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
	}
}

QTableWidgetItem *TableWidget::itemFactory(const QString &text) {

	QTableWidgetItem* item = new QTableWidgetItem(text);
	item->setTextAlignment( Qt::AlignCenter | Qt::AlignHCenter );
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);

	return item;
}
