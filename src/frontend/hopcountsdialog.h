#ifndef HOPCOUNTSDIALOG_H
#define HOPCOUNTSDIALOG_H

#include <QDialog>
#include "backend/hopcountstable.h"

namespace Ui {
class HopCountsDialog;
}

class HopCountsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit HopCountsDialog(const HopCountsTable& hopCounts, QWidget *parent = 0);
	~HopCountsDialog();

private:
	Ui::HopCountsDialog *ui;
};

#endif // HOPCOUNTSDIALOG_H
