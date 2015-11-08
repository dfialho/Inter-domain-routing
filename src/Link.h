#ifndef LINK_H
#define LINK_H


#include "Node.h"

class Link {

public:
    enum Type { Customer = 0, Peer = 1, Provider = 2 };

    Link(Node* tail, Node* head, Type type)
            : tail(tail), head(head), type(type) {}

    inline Node* getTail() const { return tail; }
    inline Node* getHead() const { return head; }
    inline Link::Type getType() const { return type; }

private:
    Node* tail;
    Node* head;
    Link::Type type;

};


#endif //LINK_H
