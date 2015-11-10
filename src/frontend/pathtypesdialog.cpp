#include "pathtypesdialog.h"
#include "ui_pathtypesdialog.h"

PathTypesDialog::PathTypesDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PathTypesDialog) {

	ui->setupUi(this);


}

PathTypesDialog::~PathTypesDialog()
{
	delete ui;
}
