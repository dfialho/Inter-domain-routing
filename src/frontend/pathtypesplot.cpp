#include "pathtypesplot.h"
#include "../backend/StatsTable.h"
#include "../backend/Network.h"

QVector<double> PathTypesPlot::dataX() const {

	QVector<double> types;
	types << Network::PathType::Customer << Network::PathType::Peer << Network::PathType::Provider;

	return types;
}

double PathTypesPlot::rangeX() const {
	return 3;
}

QVector<double> PathTypesPlot::dataY() const {

	QVector<double> counts;
	counts << statsTable->getCount(Network::PathType::Customer) <<
			  statsTable->getCount(Network::PathType::Peer) <<
			  statsTable->getCount(Network::PathType::Provider);

	return counts;
}

double PathTypesPlot::rangeY() const {

	return std::max(std::max(statsTable->getCount(Network::PathType::Customer),
							 statsTable->getCount(Network::PathType::Peer)),
					statsTable->getCount(Network::PathType::Provider));
}
