#ifndef NETWORK_H
#define NETWORK_H

#include "Node.h"
#include "NetworkIdGenerator.h"
#include "Link.h"
#include "pathtypestable.h"
#include "pathtype.h"

class StatsTable;

class Network {

public:
    typedef std::vector<unsigned> HopCountList;
    typedef std::unique_ptr<Node> NodeHolder;
    typedef std::vector<NodeHolder> NodeHolderList;

    Network() {}
    Network(const std::string& filename);

    void addLink(Node::ID tailId, Node::ID headId, Link::Type type);
    void print() const;

	PathTypesTable findPathTypes(Node::ID destNodeId);
    HopCountList findPathHopCounts(Node::ID destNodeId);
    void stats(StatsTable& statsTable);

    inline const NodeHolder& getNode(Node::ID id) { return nodes[idGenerator.getNetworkId(id)]; }
    inline const NodeHolderList& getNodes() const { return nodes; }
    inline unsigned long nodeCount() { return nodes.size(); }

private:
    NodeHolderList nodes;           // all the nodes in the network
    NetworkIdGenerator idGenerator; // generates and holds the nodes ids

	PathType operation(Link::Type linkType, PathType pathType);

	void findPathTypes(Node::ID destNodeNetId, PathTypesTable& pathTypes);
	void findPathHopCounts(Node::ID destNodeNetId, const PathTypesTable& pathTypes, HopCountList& hopCounts);

};


#endif //NETWORK_H
