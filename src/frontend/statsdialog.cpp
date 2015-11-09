#include "../backend/Network.h"
#include "../backend/StatsTable.h"

#include "hopcountsplot.h"
#include "pathtypesplot.h"
#include "statsdialog.h"
#include "ui_statsdialog.h"

StatsDialog::StatsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::StatsDialog),
	currentWidget(nullptr) {

	ui->setupUi(this);

	Network network("/home/david/Development/IST/ADRC/Inter-domain-routing/tests/enunciado_ext1.txt");

	// connection for the combox to make the widget change when the user chooses what stat to see
	connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxCurrentIndexChanged(int)));

	StatsTable table;
	network.stats(table);
	statsTable = &table;

	// create the widgets to be interchanged according to the combo box index
	PathTypesPlot* pathTypesPlot = new PathTypesPlot(this);
	pathTypesPlot->setTable(statsTable);
	HopCountsPlot* hopCountsPlot = new HopCountsPlot(this);
	hopCountsPlot->setTable(statsTable);
//	StatsTableWidget* tableWidget = new StatsTableWidget(this);
//	tableWidget->setTable(statsTable);
	QPushButton* tableWidget = new QPushButton(this);

	this->widgets << tableWidget << pathTypesPlot << hopCountsPlot;

	// hide all widgets - only thw current widget is supposed to be shown
	for(auto widget : widgets) {
		widget->hide();
	}

	// setup combox box
	comboBoxItems << "All" << "Path Types" << "Hop Counts";
	ui->comboBox->addItems(comboBoxItems);
}

StatsDialog::~StatsDialog()
{
	delete ui;
}


void StatsDialog::onComboBoxCurrentIndexChanged(int index){
	if(currentWidget == nullptr) {
		ui->verticalLayout->addWidget(widgets[index]);
	} else {
		ui->verticalLayout->removeWidget(currentWidget);
		currentWidget->hide();
		ui->verticalLayout->addWidget(widgets[index]);
	}

	currentWidget = widgets[index];
	currentWidget->show();
}
