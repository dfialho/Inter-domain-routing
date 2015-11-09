#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>

class TableWidget : public QTableWidget {

public:
	TableWidget(int rowCount, int columnCount, QWidget *parent = 0);

	static QTableWidgetItem* itemFactory(const QString& text);

};

#endif // TABLEWIDGET_H
