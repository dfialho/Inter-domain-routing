#include "NetworkIdGenerator.h"

uint16_t NetworkIdGenerator::getNetworkId(Node::ID id) {
    auto result = this->idMap.insert(std::make_pair(id, this->netIdCount));
    if(result.second) {
        // the node was inserted which means it is a new node
        this->netIdCount++;
    }

    // return the mapped value which is the node's network id
    return result.first->second;
}
