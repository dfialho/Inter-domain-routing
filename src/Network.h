#ifndef NETWORK_H
#define NETWORK_H

#include "Node.h"
#include "NetworkIdGenerator.h"
#include "Link.h"

class Network {

public:
    enum PathType { Customer = 0, Peer = 1, Provider = 2, None = 3 };
    typedef std::vector<PathType> PathTypeList;
    typedef std::vector<unsigned> HopCountList;
    typedef std::unique_ptr<Node> NodeHolder;
    typedef std::vector<NodeHolder> NodeHolderList;

    Network() {}
    Network(const std::string& filename);

    void addLink(Node::ID tailId, Node::ID headId, Link::Type type);
    void print() const;

    PathTypeList findPathTypes(Node::ID destNodeId);
    HopCountList findPathHopCounts(Node::ID destNodeId);

    inline const NodeHolder& getNode(Node::ID id) { return nodes[idGenerator.getNetworkId(id)]; }
    inline const NodeHolderList& getNodes() const { return nodes; }
    inline unsigned long nodeCount() { return nodes.size(); }

private:
    NodeHolderList nodes;           // all the nodes in the network
    NetworkIdGenerator idGenerator; // generates and holds the nodes ids

    PathType operation(Link::Type linkType, Network::PathType pathType);
};


#endif //NETWORK_H
