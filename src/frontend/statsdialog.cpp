#include "../backend/Network.h"
#include "../backend/StatsTable.h"

#include "hopcountsplot.h"
#include "pathtypesplot.h"
#include "statsdialog.h"
#include "tablewidget.h"
#include "ui_statsdialog.h"

StatsDialog::StatsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::StatsDialog),
	currentWidget(nullptr) {

	ui->setupUi(this);

	Network network("/home/david/Development/IST/ADRC/Inter-domain-routing/tests/enunciado_ext1.txt");

	// connection for the combox to make the widget change when the user chooses what stat to see
	connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxCurrentIndexChanged(int)));

	StatsTable statsTable;
	network.stats(statsTable);

	// create the widgets to be interchanged according to the combo box index
	PathTypesPlot* pathTypesPlot = new PathTypesPlot(this);
	pathTypesPlot->setTable(&statsTable);
	HopCountsPlot* hopCountsPlot = new HopCountsPlot(this);
	hopCountsPlot->setTable(&statsTable);
	TableWidget* tableWidget = new TableWidget(statsTable.getMaxHop(), 3, this);
	setTable(tableWidget, statsTable);

	this->widgets << tableWidget << pathTypesPlot << hopCountsPlot;

	// hide all widgets - only the current widget is supposed to be shown
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

void StatsDialog::setTable(TableWidget* tableWidget, const StatsTable &statsTable) {

	// setup header labels
	QStringList horizontalLabels;
	horizontalLabels << "Customer" << "Peer" << "Provider";
	tableWidget->setHorizontalHeaderLabels(horizontalLabels);

	for(unsigned i = 0; i < statsTable.getMaxHop() + 1; i++) {
		// set vertical headr with the hop count
		QTableWidgetItem* item = TableWidget::itemFactory(QString::number(i));
		tableWidget->setVerticalHeaderItem(i, item);

		// add count for the customer
		item = TableWidget::itemFactory(QString::number(statsTable.getCount(i, Network::PathType::Customer)));
		tableWidget->setItem(i, Network::PathType::Customer, item);

		// add count for the peer
		item = TableWidget::itemFactory(QString::number(statsTable.getCount(i, Network::PathType::Peer)));
		tableWidget->setItem(i, Network::PathType::Peer, item);

		// add count for the provider
		item = TableWidget::itemFactory(QString::number(statsTable.getCount(i, Network::PathType::Provider)));
		tableWidget->setItem(i, Network::PathType::Provider, item);
	}
}
