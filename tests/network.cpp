#include <iostream>
#include "../src/Network.h"

using namespace std;


int main() {

    Network network("/home/david/Development/IST/ADRC/Inter-domain-routing/tests/NewLargeNetwork.txt");

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
    Network::StatsTable table = network.stats();
    end = clock();
    cout << double(end - begin) / CLOCKS_PER_SEC << endl;

    cout << "Stats" << endl;
    cout << "Hop\tC\tR\tP\tNone" << endl;
    for(auto i = 0; i < table.size(); i++) {
        cout << i << '\t' << table[i][0] << '\t' << table[i][1] << '\t' << table[i][2] << '\t' << table[i][3] << endl;
    }
}