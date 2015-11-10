#ifndef PATHTYPESDIALOG_H
#define PATHTYPESDIALOG_H

#include <QDialog>

namespace Ui {
class PathTypesDialog;
}

class PathTypesDialog : public QDialog {
	Q_OBJECT

public:
	explicit PathTypesDialog(const Network, QWidget *parent = 0);
	~PathTypesDialog();

private:
	Ui::PathTypesDialog *ui;

};

#endif // PATHTYPESDIALOG_H
