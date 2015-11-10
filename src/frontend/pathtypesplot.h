#ifndef PATHTYPESPLOT_H
#define PATHTYPESPLOT_H

#include "statsplot.h"

class PathTypesPlot : public StatsPlot {

public:
	PathTypesPlot(QWidget *parent = 0) : StatsPlot(parent) {}

protected:
	virtual QVector<double> dataX() const;
	virtual double rangeX() const;
	virtual QVector<double> dataY() const;
	virtual double rangeY() const;

};

#endif // PATHTYPESPLOT_H
