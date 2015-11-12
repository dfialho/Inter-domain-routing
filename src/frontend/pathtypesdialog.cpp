#include "pathtypesdialog.h"
#include "tablewidget.h"
#include "ui_pathtypesdialog.h"
#include "backend/Network.h"

#include <QVBoxLayout>

PathTypesDialog::PathTypesDialog(const Network::NodeHolderList& nodes, const PathTypesTable &pathTypes, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PathTypesDialog) {

	ui->setupUi(this);

	// create the table widget with 1 column for the path types
	TableWidget* tableWidget = new TableWidget(pathTypes.size(), 1, this);

	// setup the horizontal header label
	QStringList horizontalLabels;
	horizontalLabels << "Prices";
	tableWidget->setHorizontalHeaderLabels(horizontalLabels);

	// setup the vertical headers with the node's ids
	QStringList nodeIds;
	for(auto& nodesPrices : pathTypes) {
		nodeIds << QString::number(nodesPrices.first);
	}

	tableWidget->setHorizontalHeaderLabels(horizontalLabels);

	// introduce path types in the table
	for(unsigned i = 0; i < pathTypes.size(); i++) {

		// convert path type to string
		QString type;
		switch(pathTypes[i]) {
			case PathType::Customer:
				type = "customer";
				break;
			case PathType::Peer:
				type = "peer";
				break;
			case PathType::Provider:
				type = "provider";
				break;
			case PathType::None:
				type = "none";
				break;
		}

		tableWidget->setItem(i, 0, TableWidget::itemFactory(type));
	}

	// set nodes ids as vertical headers
	QStringList verticalLabels;

	for(const auto& node : nodes) {
		verticalLabels << QString::number(node->getId());
	}

	tableWidget->setVerticalHeaderLabels(verticalLabels);

	this->setLayout(new QVBoxLayout(this));
	this->layout()->addWidget(tableWidget);
}

PathTypesDialog::~PathTypesDialog() {
	delete ui;
}
