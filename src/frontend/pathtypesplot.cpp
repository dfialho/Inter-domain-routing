#include "pathtypesplot.h"
#include "../backend/StatsTable.h"
#include "../backend/Network.h"

QVector<double> PathTypesPlot::dataX() const {

	QVector<double> types;
	types << PathType::Customer << PathType::Peer << PathType::Provider;

	return types;
}

double PathTypesPlot::rangeX() const {
	return 3;
}

QVector<double> PathTypesPlot::dataY() const {

	QVector<double> counts;
	counts << statsTable->getCount(PathType::Customer) <<
			  statsTable->getCount(PathType::Peer) <<
			  statsTable->getCount(PathType::Provider);

	return counts;
}

double PathTypesPlot::rangeY() const {

	return std::max(std::max(statsTable->getCount(PathType::Customer),
							 statsTable->getCount(PathType::Peer)),
					statsTable->getCount(PathType::Provider));
}
