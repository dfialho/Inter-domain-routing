#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>

class StatsTable;

namespace Ui {
class StatsDialog;
}

class StatsDialog : public QDialog {
	Q_OBJECT

public:
	explicit StatsDialog(QWidget *parent = 0);
	~StatsDialog();

private slots:
	void onComboBoxCurrentIndexChanged(int index);

private:
	Ui::StatsDialog *ui;

	QStringList comboBoxItems;
	QList<QWidget*> widgets;
	const StatsTable* statsTable;
	QWidget* currentWidget;

};

#endif // STATSDIALOG_H
