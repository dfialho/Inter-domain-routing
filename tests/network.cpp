#include <iostream>
#include "../src/Network.h"
#include "../src/StatsTable.h"

using namespace std;


int main() {

    Network network("/home/david/Development/IST/ADRC/Inter-domain-routing/tests/small.txt");

    cout << "Initial Network" << endl;
    network.print();
    cout << endl;

    clock_t begin, end;

    begin = clock();
    Network::PathTypeList pathTypes = network.findPathTypes(5);
    end = clock();
    cout << double(end - begin) / CLOCKS_PER_SEC << endl;

    const Network::NodeHolderList& nodes = network.getNodes();

    cout << "PathTypes" << endl;
    for(auto i = 0; i < network.nodeCount(); i++) {
        cout << nodes[i]->getId() << ": " << pathTypes[i] << endl;
    }

    begin = clock();
    for(auto& node : network.getNodes()) {
        network.findPathTypes(node->getId());
    }
    end = clock();
    cout << double(end - begin) / CLOCKS_PER_SEC << endl;

    begin = clock();
    Network::HopCountList hopCounts = network.findPathHopCounts(5);
    end = clock();
    cout << double(end - begin) / CLOCKS_PER_SEC << endl;

    cout << "Hop Counts" << endl;
    for(auto i = 0; i < network.nodeCount(); i++) {
        cout << nodes[i]->getId() << ": " << hopCounts[i] << endl;
    }

    begin = clock();
    StatsTable table;
    network.stats(table);
    end = clock();
    cout << double(end - begin) / CLOCKS_PER_SEC << endl;

    cout << "Stats" << endl;
    cout << "Hop\tC\tR\tP\tNone" << endl;
    for(unsigned i = 0; i < table.getMaxHop() + 1; i++) {
        cout << i << '\t' <<
                table.getCount(i, Network::PathType::Customer) << '\t' <<
                table.getCount(i, Network::PathType::Peer) << '\t' <<
                table.getCount(i, Network::PathType::Provider) << '\t' <<
                endl;
    }
}