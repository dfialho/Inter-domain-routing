#include <fstream>
#include <unistd.h>
#include <iostream>

#include "Network.h"

using namespace std;

Network::Network(const std::string &filename) {

    ifstream inFile(filename, ifstream::in);

    if(!inFile.is_open()) {
        throw string("can't open input file");
    }

    uint16_t tailId, headId, relationship;
    while(inFile >> tailId >> headId >> relationship) {
        addLink(tailId, headId, LinkType(relationship));
    }
}

void Network::addLink(Node::ID tailId, Node::ID headId, LinkType type) {

    // get the network ids for both the nodes of the link
    Node::ID headNetId = idGenerator.getNetworkId(headId);
    Node::ID tailNetId = idGenerator.getNetworkId(tailId);

    // add the nodes to the nodes list
    if(headNetId >= nodes.size()) {
        nodes.push_back(NodeHolder(new Node(headId, headNetId)));
    }

    if(tailNetId >= nodes.size()) {
        nodes.push_back(NodeHolder(new Node(tailId, tailNetId)));
    }

    switch (type) {
        case LinkType::Customer:
            // add  customer link from the tail node to the head node
            nodes[tailNetId]->addCustomer(nodes[headNetId].get());
            break;
        case LinkType::Peer:
            // add  peer link from the tail node to the head node
            nodes[tailNetId]->addPeer(nodes[headNetId].get());
            break;
        case LinkType::Provider:
            // add  peer provider from the tail node to the head node
            nodes[tailNetId]->addProvider(nodes[headNetId].get());
            break;
    }
}

void Network::print() const {
    for(auto& node : nodes) {
        cout << node->getId() << ":" << endl;

        for(auto& customer : node->getCustomers()) {
            cout << "\tC-" << customer->getId() << endl;
        }

        for(auto& peer : node->getPeers()) {
            cout << "\tR-" << peer->getId() << endl;
        }

        for(auto& provider : node->getProviders()) {
            cout << "\tP-" << provider->getId() << endl;
        }
    }
}
