#include "hopcountsdialog.h"
#include "tablewidget.h"
#include "ui_hopcountsdialog.h"

#include <QVBoxLayout>

HopCountsDialog::HopCountsDialog(const Network::NodeHolderList& nodes,
								 const HopCountsTable &hopCounts, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::HopCountsDialog) {

	ui->setupUi(this);

	// create the table widget with 2 columns for the path types and hop counts
	TableWidget* tableWidget = new TableWidget(hopCounts.size(), 2, this);

	// setup the horizontal header label
	QStringList horizontalLabels;
	horizontalLabels << "Prices" << "Hops";
	tableWidget->setHorizontalHeaderLabels(horizontalLabels);

	// setup the vertical headers with the node's ids
	// introduce path types and hop counts in the table
	QStringList nodeIds;
	unsigned i = 0;
	for(auto& hops : hopCounts) {
		nodeIds << QString::number(hops.nodeId);

		// convert path type to string
		QString type;
		switch(hops.pathType) {
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
		tableWidget->setItem(i, 1, TableWidget::itemFactory(QString::number(hops.hopCount)));

		i++;
	}

	tableWidget->setHorizontalHeaderLabels(horizontalLabels);

	// set nodes ids as vertical headers
	QStringList verticalLabels;

	for(const auto& node : nodes) {
		verticalLabels << QString::number(node->getId());
	}

	tableWidget->setVerticalHeaderLabels(verticalLabels);

	this->setLayout(new QVBoxLayout(this));
	this->layout()->addWidget(tableWidget);
}

HopCountsDialog::~HopCountsDialog()
{
	delete ui;
}
