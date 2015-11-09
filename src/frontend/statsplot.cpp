#include "statsplot.h"
#include "../backend/StatsTable.h"

void StatsPlot::setTable(const StatsTable *statsTable) {

	this->statsTable = statsTable;

	if(barsPlot != nullptr) {
		this->removePlottable(barsPlot);
	}

	barsPlot = new QCPBars(xAxis, yAxis);
	this->addPlottable(barsPlot);

	// setup the X Axis
	xAxis->setAutoTicks(false);
	xAxis->setTickVector(this->dataX());
	xAxis->setSubTickCount(0);
	xAxis->grid()->setVisible(true);
	xAxis->setRange(-1, this->rangeX());

	// setup the Y Axis
	yAxis->setTickLength(0, 2);
	yAxis->grid()->setVisible(true);
	yAxis->setRange(0, this->rangeY());

	barsPlot->setData(this->dataX(), this->dataY());
	this->replot();
}
