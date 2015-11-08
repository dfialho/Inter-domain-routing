#include <fstream>
#include <iostream>

#include "Network.h"
#include "LinkPriorityQueue.h"

using namespace std;

Network::Network(const std::string &filename) {

    ifstream inFile(filename, ifstream::in);

    if(!inFile.is_open()) {
        throw string("can't open input file");
    }

    uint16_t tailId, headId, relationship;
    while(inFile >> tailId >> headId >> relationship) {
        addLink(tailId, headId, Link::Type (relationship - 1));
    }
}

void Network::addLink(Node::ID tailId, Node::ID headId, Link::Type  type) {

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
        case Link::Type ::Customer:
            // add  customer link from the tail node to the head node
            nodes[tailNetId]->addCustomer(nodes[headNetId].get());
            break;
        case Link::Type ::Peer:
            // add  peer link from the tail node to the head node
            nodes[tailNetId]->addPeer(nodes[headNetId].get());
            break;
        case Link::Type ::Provider:
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

Network::PathTypeList Network::findPathTypes(Node::ID destNodeId) {

    // get the destination node network id
    Node::ID destNodeNetId = idGenerator.getNetworkId(destNodeId);

    // initialize all nodes with path type = None
    PathTypeList pathTypes(nodes.size(), PathType::None);

    LinkPriorityQueue linkQueue;
    pathTypes[destNodeNetId] = PathType::Customer;

    linkQueue.pushCustomers(nodes[destNodeNetId].get());
    linkQueue.pushPeers(nodes[destNodeNetId].get());
    linkQueue.pushProviders(nodes[destNodeNetId].get());

    while(!linkQueue.empty()) {
        Link link = linkQueue.pop();
        Node* node = link.getHead();

        PathType newPathType = operation(link.getType(), pathTypes[link.getTail()->getNetid()]);
        if(newPathType < pathTypes[node->getNetid()]) {
            pathTypes[node->getNetid()] = newPathType;

            linkQueue.pushCustomers(node);

            if(newPathType == PathType::Customer) {
                linkQueue.pushPeers(node);
                linkQueue.pushProviders(node);
            }
        }
    }

    return pathTypes;
}

Network::PathType Network::operation(Link::Type linkType, Network::PathType pathType) {
    static PathType table[3][5] = {
            {PathType::Provider, PathType::Provider, PathType::Provider, PathType::Provider, PathType::None},
            {PathType::Peer,     PathType::Peer,     PathType::None,     PathType::None,     PathType::None},
            {PathType::Customer, PathType::Customer, PathType::None,     PathType::None,     PathType::None}
    };

    return table[linkType][pathType];
}
