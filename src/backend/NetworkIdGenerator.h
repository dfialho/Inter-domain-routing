#ifndef NETWORKIDGENERATOR_H
#define NETWORKIDGENERATOR_H


#include <unordered_map>
#include "Node.h"

class NetworkIdGenerator {

public:
    NetworkIdGenerator() : netIdCount(0) {}

    Node::ID getNetworkId(Node::ID id);

private:
    Node::ID netIdCount;                          // counter to assign unique network ids in order
    std::unordered_map<Node::ID, Node::ID> idMap; // maps node ids to network ids

};


#endif //NETWORKIDGENERATOR_H
