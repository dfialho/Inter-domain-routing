#ifndef LINKPRIORITYQUEUE_H
#define LINKPRIORITYQUEUE_H


#include <queue>
#include "Node.h"
#include "Link.h"
#include "Network.h"

class LinkPriorityQueue {

public:
    LinkPriorityQueue() {}

    void push(const Link& link);
    void pushCustomers(Node* node);
    void pushPeers(Node* node);
    void pushProviders(Node* node);
    Link pop();

    inline bool empty() {
        return customerQueue.empty() && peerQueue.empty() && providerQueue.empty();
    }

private:
    std::queue<Link> customerQueue;
    std::queue<Link> peerQueue;
    std::queue<Link> providerQueue;

};


#endif //LINKPRIORITYQUEUE_H
