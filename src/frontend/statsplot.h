#ifndef STATSPLOT_H
#define STATSPLOT_H

#include "qcustomplot.h"

class StatsTable;

class StatsPlot : public QCustomPlot {

public:
	StatsPlot(QWidget *parent = 0) : QCustomPlot(parent), statsTable(nullptr), barsPlot(nullptr) {}

	void setTable(const StatsTable* statsTable);

protected:

	virtual QVector<double> dataX() const = 0;
	virtual double rangeX() const = 0;
	virtual QVector<double> dataY() const = 0;
	virtual double rangeY() const = 0;

	const StatsTable* statsTable;

private:
	QCPBars* barsPlot;

};

#endif // STATSPLOT_H
