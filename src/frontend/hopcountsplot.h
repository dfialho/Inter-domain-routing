#ifndef HOPCOUNTSPLOT_H
#define HOPCOUNTSPLOT_H

#include "statsplot.h"

class HopCountsPlot : public StatsPlot {

public:
	HopCountsPlot(QWidget *parent = 0) : StatsPlot(parent) {}

protected:
	virtual QVector<double> dataX() const;
	virtual double rangeX() const;
	virtual QVector<double> dataY() const;
	virtual double rangeY() const;

};

#endif // HOPCOUNTSPLOT_H
