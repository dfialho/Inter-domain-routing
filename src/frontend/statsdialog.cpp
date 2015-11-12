#include "../backend/Network.h"
#include "../backend/StatsTable.h"

#include "hopcountsplot.h"
#include "pathtypesplot.h"
#include "statsdialog.h"
#include "tablewidget.h"
#include "ui_statsdialog.h"

StatsDialog::StatsDialog(const StatsTable& statsTable, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::StatsDialog),
	currentWidget(nullptr) {

	ui->setupUi(this);

	// create the widgets to be interchanged according to the combo box index
	PathTypesPlot* pathTypesPlot = new PathTypesPlot(this);
	pathTypesPlot->setTable(&statsTable);
	HopCountsPlot* hopCountsPlot = new HopCountsPlot(this);
	hopCountsPlot->setTable(&statsTable);
	TableWidget* tableWidget = new TableWidget(statsTable.getMaxHop() + 1, 3, this);
	setTable(tableWidget, statsTable);

	this->widgets << tableWidget << pathTypesPlot << hopCountsPlot;

	ui->noneCountValue->setText(QString::number(statsTable.getCount(PathType::None)));

	// hide all widgets - only the current widget is supposed to be shown
	for(auto widget : widgets) {
		widget->hide();
	}

	// connection for the combox to make the widget change when the user chooses what stat to see
	connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxCurrentIndexChanged(int)));

	// setup combox box
	comboBoxItems << "All" << "Path Types" << "Hop Counts";
	ui->comboBox->addItems(comboBoxItems);
}

StatsDialog::~StatsDialog() {
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
		item = TableWidget::itemFactory(QString::number(statsTable.getCount(i, PathType::Customer)));
		tableWidget->setItem(i, PathType::Customer, item);

		// add count for the peer
		item = TableWidget::itemFactory(QString::number(statsTable.getCount(i, PathType::Peer)));
		tableWidget->setItem(i, PathType::Peer, item);

		// add count for the provider
		item = TableWidget::itemFactory(QString::number(statsTable.getCount(i, PathType::Provider)));
		tableWidget->setItem(i, PathType::Provider, item);

	}
}
