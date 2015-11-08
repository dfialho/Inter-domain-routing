#ifndef NODE_H
#define NODE_H


#include <cstdint>
#include <vector>
#include <memory>

class Node {

public:
    typedef uint16_t ID;
    typedef std::vector<Node*> NodeList;

    Node(ID id, ID netid) : id(id), netid(netid) {}

    inline ID getId() const { return id; }
    inline ID getNetid() const { return netid; }

    inline const NodeList &getCustomers() const { return customers; }
    inline const NodeList &getPeers() const { return peers; }
    inline const NodeList &getProviders() const { return providers; }

    inline void addCustomer(Node* node) { customers.push_back(node); }
    inline void addPeer(Node* node)  { peers.push_back(node); }
    inline void addProvider(Node* node)  { providers.push_back(node); }

private:
    ID id;      // actual id of the node
    ID netid;   // id of the node inside the network

    // lists to hold the neighbours of the node
    NodeList customers;
    NodeList peers;
    NodeList providers;

};


#endif //NODE_H
