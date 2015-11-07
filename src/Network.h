#ifndef NETWORK_H
#define NETWORK_H

#include "Node.h"
#include "NetworkIdGenerator.h"
#include "Link.h"

class Network {

public:

    Network() {}
    Network(const std::string& filename);

    void addLink(Node::ID tailId, Node::ID headId, Link::Type type);
    void print() const;

private:
    typedef std::unique_ptr<Node> NodeHolder;
    typedef std::vector<std::unique_ptr<Node>> NodeHolderList;

    NodeHolderList nodes;              // all the nodes in the network
    NetworkIdGenerator idGenerator; // generates and holds the nodes ids
};


#endif //NETWORK_H
