#include <fstream>
#include <iostream>
#include <climits>

#include "Network.h"
#include "LinkPriorityQueue.h"
#include "StatsTable.h"

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

PathTypesTable Network::findPathTypes(Node::ID destNodeId) {

    // get the destination node network id
    Node::ID destNodeNetId = idGenerator.getNetworkId(destNodeId);
    // initialize all nodes with path type = None
	PathTypesTable pathTypes(nodes.size());

	findPathTypes(destNodeNetId, pathTypes);
    return pathTypes;
}

HopCountsTable Network::findPathHopCounts(Node::ID destNodeId) {

    // get the destination node network id
    Node::ID destNodeNetId = idGenerator.getNetworkId(destNodeId);

	PathTypesTable pathTypes = findPathTypes(destNodeId);
    // initialize all nodes with path type = None
	HopCountsTable hopCounts(pathTypes);

    findPathHopCounts(destNodeNetId, pathTypes, hopCounts);
    return hopCounts;
}

void Network::stats(StatsTable &statsTable) {

    // initialize all nodes with path type = None
	PathTypesTable pathTypes(nodes.size());
    // initialize all nodes with path type = None
	HopCountsTable hopCounts(pathTypes);

    for(auto& node : nodes) {

        findPathTypes(node->getNetid(), pathTypes);
        findPathHopCounts(node->getNetid(), pathTypes, hopCounts);

		for(unsigned i = 0; i < nodeCount(); i++) {

            unsigned hopCount = hopCounts[i];

            if(hopCount == UINT_MAX) {
                // ignore None paths for now
                continue;
            }

			statsTable.add(hopCount, pathTypes[i]);

        }

		pathTypes.reset();
		hopCounts.reset();
    }
}

///// Begin Private /////

PathType Network::operation(Link::Type linkType, PathType pathType) {
    static PathType table[3][5] = {
            {PathType::Provider, PathType::Provider, PathType::Provider, PathType::Provider, PathType::None},
            {PathType::Peer,     PathType::Peer,     PathType::None,     PathType::None,     PathType::None},
            {PathType::Customer, PathType::Customer, PathType::None,     PathType::None,     PathType::None}
    };

    return table[linkType][pathType];
}

void Network::findPathTypes(Node::ID destNodeNetId, PathTypesTable &pathTypes) {

    LinkPriorityQueue linkQueue;
	pathTypes.set(destNodeNetId, nodes[destNodeNetId]->getId(), PathType::Customer);

    linkQueue.pushCustomers(nodes[destNodeNetId].get());
    linkQueue.pushPeers(nodes[destNodeNetId].get());
    linkQueue.pushProviders(nodes[destNodeNetId].get());

    while(!linkQueue.empty()) {
        Link link = linkQueue.pop();
        Node* node = link.getHead();

		PathType newPathType = operation(link.getType(), pathTypes[link.getTail()->getNetid()]);
		if(newPathType < pathTypes[node->getNetid()]) {
			pathTypes.set(node->getNetid(), node->getId(), newPathType);

            linkQueue.pushCustomers(node);

            if(newPathType == PathType::Customer) {
                linkQueue.pushPeers(node);
                linkQueue.pushProviders(node);
            }
        }
    }
}

void Network::findPathHopCounts(Node::ID destNodeNetId, const PathTypesTable& pathTypes,
								HopCountsTable &hopCounts) {

    hopCounts[destNodeNetId] = 0;
    std::queue<Link> linkQueue;

    for(auto customer : nodes[destNodeNetId]->getCustomers()) {
        linkQueue.push(Link(nodes[destNodeNetId].get(), customer, Link::Type::Customer));
    }
    for(auto peer : nodes[destNodeNetId]->getPeers()) {
        linkQueue.push(Link(nodes[destNodeNetId].get(), peer, Link::Type::Peer));
    }
    for(auto provider : nodes[destNodeNetId]->getProviders()) {
        linkQueue.push(Link(nodes[destNodeNetId].get(), provider, Link::Type::Provider));
    }

    while(!linkQueue.empty()) {
        Link link = linkQueue.front();
        linkQueue.pop();
        Node* node = link.getHead();

        unsigned newHopCount = hopCounts[link.getTail()->getNetid()] + 1;
        if(newHopCount < hopCounts[node->getNetid()]) {
            hopCounts[node->getNetid()] = newHopCount;

            for(auto customer : node->getCustomers()) {
                if(customer != link.getTail())
                    linkQueue.push(Link(node, customer, Link::Type::Customer));
            }

			if(pathTypes[node->getNetid()] == PathType::Customer) {
                for(auto peer : node->getPeers()) {
                    if(peer != link.getTail())
                        linkQueue.push(Link(node, peer, Link::Type::Peer));
                }
                for(auto provider : node->getProviders()) {
                    if(provider != link.getTail())
                        linkQueue.push(Link(node, provider, Link::Type::Provider));
                }
            }
        }
    }
}
