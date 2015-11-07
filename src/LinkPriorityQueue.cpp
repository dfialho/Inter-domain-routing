#include "LinkPriorityQueue.h"


void LinkPriorityQueue::push(const Link &link) {

    if(link.getType() == Link::Type::Customer) {
        customerQueue.push(link);
    } else if(link.getType() == Link::Type::Peer) {
        peerQueue.push(link);
    } else if(link.getType() == Link::Type::Provider) {
        providerQueue.push(link);
    }
}

void LinkPriorityQueue::pushCustomers(Node* node) {

    for(auto& customer : node->getCustomers()) {
        customerQueue.push(Link(node, customer, Link::Type::Customer));
    }
}

void LinkPriorityQueue::pushPeers(Node* node) {

    for(auto& peer : node->getPeers()) {
        peerQueue.push(Link(node, peer, Link::Type::Peer));
    }
}

void LinkPriorityQueue::pushProviders(Node* node) {

    for (auto& provider : node->getProviders()) {
        providerQueue.push(Link(node, provider, Link::Type::Provider));
    }
}

Link LinkPriorityQueue::pop() {

    std::queue<Link>* queueToPop = nullptr;

    if(!providerQueue.empty()) {
        queueToPop = &providerQueue;
    } else if(!peerQueue.empty()) {
        queueToPop = &peerQueue;
    } else {
        queueToPop = &customerQueue;
    }

    Link& link = queueToPop->front();
    queueToPop->pop();
    return link;
}
