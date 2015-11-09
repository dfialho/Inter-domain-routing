#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>

class TableWidget : public QTableWidget {

public:
	TableWidget(QWidget* parent = 0);
	TableWidget(int rowCount, int columnCount, QWidget *parent = 0);

protected:
	QTableWidgetItem* itemFactory(const QString& text);

};

#endif // TABLEWIDGET_H
