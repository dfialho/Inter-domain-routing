#ifndef STATSTABLE_H
#define STATSTABLE_H


#include "Network.h"

class StatsTable {

public:

	StatsTable() : counts(1, {0}), hopsCounts(1, 0), maxHopCount(0)  {
        pathTypeCount = {0};
    }

    inline unsigned getCount(unsigned hops) const { return hopsCounts[hops]; }
    inline unsigned getCount(Network::PathType pathType) const { return pathTypeCount[pathType]; }
    inline unsigned getCount(unsigned hops, Network::PathType pathType) const { return counts[hops][pathType]; }
    inline unsigned getMaxHop() const { return maxHopCount; }

    void add(unsigned hops, Network::PathType pathType);

private:
    std::vector<std::array<unsigned, 4>> counts;
    std::array<unsigned, 4> pathTypeCount;
    std::vector<unsigned> hopsCounts;
    unsigned maxHopCount;

};


#endif //STATSTABLE_H
