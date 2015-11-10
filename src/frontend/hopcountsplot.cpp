#include "hopcountsplot.h"
#include "../backend/StatsTable.h"

QVector<double> HopCountsPlot::dataX() const {

	QVector<double> hops;
	for(unsigned i = 0; i < statsTable->getMaxHop() + 1; i++) {
		hops << i;
	}

	return hops;
}

double HopCountsPlot::rangeX() const {
	return statsTable->getMaxHop() + 1;
}

QVector<double> HopCountsPlot::dataY() const {

	QVector<double> counts;
	for(unsigned i = 0; i < statsTable->getMaxHop() + 1; i++) {
		unsigned count = statsTable->getCount(i);
		counts << count;
	}

	return counts;
}

double HopCountsPlot::rangeY() const {

	unsigned maxCount = 0;
	for(unsigned i = 0; i < statsTable->getMaxHop() + 1; i++) {
		unsigned count = statsTable->getCount(i);
		if(count > maxCount) {
			maxCount = count;
		}
	}

	return maxCount + 1;
}
