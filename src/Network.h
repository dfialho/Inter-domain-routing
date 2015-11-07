#ifndef NETWORK_H
#define NETWORK_H

#include "Node.h"
#include "NetworkIdGenerator.h"

class Network {

public:
    enum LinkType { Customer = 0, Peer = 1, Provider = 2 };

    Network() {}
    Network(const std::string& filename);

    void addLink(Node::ID tailId, Node::ID headId, LinkType type);
    void print() const;

private:
    typedef std::unique_ptr<Node> NodeHolder;
    typedef std::vector<std::unique_ptr<Node>> NodeHolderList;

    NodeHolderList nodes;              // all the nodes in the network
    NetworkIdGenerator idGenerator; // generates and holds the nodes ids
};


#endif //NETWORK_H
