#include <QMessageBox>
#include "mainwindow.h"
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
	/** DEBUG **/
	ui->lineEdit->setText("/home/david/Development/IST/ADRC/Inter-domain-routing/tests/small.txt");

	// connects
	connect(ui->buttonLoad, SIGNAL(clicked(bool)), this, SLOT(onButtonLoadClicked()));
	connect(ui->buttonStart, SIGNAL(clicked(bool)), this, SLOT(onButtonStartClicked()));
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
		QMessageBox::information(this, "Path Types", "Path Types", QMessageBox::Ok);
	} else if(ui->radioButtonPathPrices->isChecked()) {
		QMessageBox::information(this, "Hop Counts", "Hop Counts", QMessageBox::Ok);
	} else if(ui->radioButtonStats->isChecked()) {
		QMessageBox::information(this, "Stats", "Stats", QMessageBox::Ok);
	}

	// renable the user input
	ui->buttonLoad->setEnabled(true);
	ui->lineEdit->setEnabled(true);
	ui->groupBox->setEnabled(true);

	// replace status message
	ui->statusbar->showMessage(currentMessage);
}
