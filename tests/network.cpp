#include <iostream>
#include "../src/Network.h"

using namespace std;


int main() {

    Network network("/home/david/Development/IST/ADRC/Inter-domain-routing/tests/enunciado_ext1.txt");

    cout << "Initial Network" << endl;
    network.print();
    cout << endl;

    clock_t begin = clock();
    Network::PathTypeList pathTypes = network.findPathTypes(5);
    clock_t end = clock();
    cout << double(end - begin) / CLOCKS_PER_SEC << endl;

    const Network::NodeHolderList& nodes = network.getNodes();
    for(auto i = 0; i < network.nodeCount(); i++) {
        cout << nodes[i]->getId() << ": " << pathTypes[i] << endl;
    }

    begin = clock();
    for(auto& node : network.getNodes()) {
        network.findPathTypes(node->getId());
    }
    end = clock();
    cout << double(end - begin) / CLOCKS_PER_SEC << endl;
}