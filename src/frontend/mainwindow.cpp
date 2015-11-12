#include <QMessageBox>
#include "backend/StatsTable.h"
#include "hopcountsdialog.h"
#include "mainwindow.h"
#include "pathtypesdialog.h"
#include "statsdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {

	ui->setupUi(this);
	this->setFixedSize(500, 166);

	// don't let the user excute any operation before loading the network
	ui->groupBox->setEnabled(false);

	// put a hint in the line edit
	ui->lineEdit->setPlaceholderText("network file path");

	// connects
	connect(ui->buttonLoad, SIGNAL(clicked(bool)), this, SLOT(onButtonLoadClicked()));
	connect(ui->buttonStart, SIGNAL(clicked(bool)), this, SLOT(onButtonStartClicked()));
	connect(ui->radioButtonStats, SIGNAL(clicked(bool)), this, SLOT(onRadioButtonStatsClicked()));
	connect(ui->radioButtonHopCounts, SIGNAL(clicked(bool)), this, SLOT(onRadioButtonHopCountsClicked()));
	connect(ui->radioButtonPathPrices, SIGNAL(clicked(bool)), this, SLOT(onRadioButtonPathTypesClicked()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onButtonLoadClicked() {

	// disable the user input
	ui->buttonLoad->setEnabled(false);
	ui->lineEdit->setEnabled(false);
	ui->groupBox->setEnabled(false);

	ui->statusbar->showMessage("Loading...");

	try {
		network.reset(new Network(ui->lineEdit->text().toStdString()));
		ui->statusbar->showMessage("Loaded: " + ui->lineEdit->text());

		// enable the execution buttons
		ui->groupBox->setEnabled(true);

	} catch(const std::string& message) {
		QMessageBox::warning(this, "Network File", "Can't open the network file", QMessageBox::Ok);
		ui->statusbar->clearMessage();
	}

	// reenable the user input
	ui->buttonLoad->setEnabled(true);
	ui->lineEdit->setEnabled(true);
}

void MainWindow::onButtonStartClicked() {
	// disable the user input
	ui->buttonLoad->setEnabled(false);
	ui->lineEdit->setEnabled(false);
	ui->groupBox->setEnabled(false);

	// store current message
	QString currentMessage = ui->statusbar->currentMessage();
	// indicating to the user that it's processing
	ui->statusbar->showMessage("processing...");

	if(ui->radioButtonHopCounts->isChecked()) {
		HopCountsTable hopCounts = network->findPathHopCounts(ui->spinBox->value());
		HopCountsDialog* dialog = new HopCountsDialog(network->getNodes(), hopCounts, this);
		dialog->show();

	} else if(ui->radioButtonPathPrices->isChecked()) {
		PathTypesTable pathTypes = network->findPathTypes(ui->spinBox->value());
		PathTypesDialog* dialog = new PathTypesDialog(network->getNodes(), pathTypes, this);
		dialog->show();

	} else if(ui->radioButtonStats->isChecked()) {
		// compute sats
		StatsTable statsTable;
		this->network->stats(statsTable);

		StatsDialog* dialog = new StatsDialog(statsTable, this);
		dialog->show();
	}

	// renable the user input
	ui->buttonLoad->setEnabled(true);
	ui->lineEdit->setEnabled(true);
	ui->groupBox->setEnabled(true);

	// replace status message
	ui->statusbar->showMessage(currentMessage);
}

void MainWindow::onRadioButtonStatsClicked() {
	ui->labelSpinBox->setEnabled(false);
	ui->spinBox->setEnabled(false);
}

void MainWindow::onRadioButtonHopCountsClicked() {
	ui->labelSpinBox->setEnabled(true);
	ui->spinBox->setEnabled(true);
}

void MainWindow::onRadioButtonPathTypesClicked() {
	ui->labelSpinBox->setEnabled(true);
	ui->spinBox->setEnabled(true);
}
