#include "StatsTable.h"

void StatsTable::add(unsigned hops, PathType pathType) {

    if(hops > maxHopCount) {
        maxHopCount = hops;
        // increase the size of the vector
        counts.resize(maxHopCount + 1, {0});
        hopsCounts.resize(maxHopCount + 1, {0});
    }

    counts[hops][pathType]++;
    pathTypeCount[pathType]++;
    hopsCounts[hops]++;
}
