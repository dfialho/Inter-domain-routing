from collections import deque
from link import Link
from node import Node
from relationship import Relationship


class Network(object):

    def __init__(self):
        self._nodes = []
        self._ids = {}
        self._netid_count = -1

    @staticmethod
    def from_file(path):
        keymap = {'3': Relationship.P, '2': Relationship.R, '1': Relationship.C}
        net = Network()
        with open(path) as file:
            for line in file:
                words = line.split()
                net.add_link(int(words[0]), int(words[1]), keymap[words[2]])
        return net

    def _new_netid(self):
        self._netid_count += 1
        return self._netid_count

    def _netid(self, id):
        try:
            netid = self._ids[id]
        except KeyError:
            netid = self._new_netid()
            self._ids[id] = netid

        return netid

    def add_link(self, tail_id, head_id, relationship):
        tail_netid = self._netid(tail_id)
        head_netid = self._netid(head_id)

        # check if the tail id is not in the nodes list
        # this is true if the ID is bigger then the current list size
        if tail_netid >= len(self._nodes):
            self._nodes.append(Node(tail_id, tail_netid))

        # check if the tail id is not in the nodes list
        if head_netid >= len(self._nodes):
            self._nodes.append(Node(head_id, head_netid))

        # add the edge to the tail node
        self._nodes[tail_netid].add_link(self._nodes[head_netid], relationship)

    def find_routes(self, dest_id):

        for node in self._nodes:
            node.path_type = Relationship.NON

        # create aux list of edges
        customer_links = deque()
        peer_links = deque()
        provider_links = deque()

        only_customers = False
        dest_node = self._nodes[self._ids[dest_id]]
        link = Link(dest_node, dest_node, Relationship.SELF)

        while link:
            # processing the path type of the head node of the link
            node = link.head

            path_type = Relationship.operation(link.type, link.tail.path_type)
            if path_type < node.path_type:
                node.path_type = path_type

                for customer in node.customers:
                    # the type of link is equal to the relationship between the head node and the tail
                    customer_links.append(Link(node, customer, Relationship.C))

                if not only_customers:
                    for peer in node.peers:
                        peer_links.append(Link(node, peer, Relationship.R))
                    for provider in node.providers:
                        provider_links.append(Link(node, provider, Relationship.P))

            if provider_links:
                link = provider_links.popleft()
            elif peer_links:
                link = peer_links.popleft()
            elif customer_links:
                link = customer_links.popleft()
                only_customers = True
            else:
                link = None

    def get_hops(self, dest_id):
        min_hops = {}
        tovisit = deque()

        # Set all the distances to infinity
        for node in self._nodes:
            min_hops[node._netid] = 4294967295 # it should be infinity here

        # Map the node to our id strategy
        node = self._nodes[self._ids[dest_id]]

        # Set the distance to self equal to zero
        min_hops[node._netid] = 0

        # Add the edge to self to the queue
        link = Link(node, node, Relationship.C)

        while link:

            node = link.head

            # Check if the current estimate is better than the estimated last
            if min_hops[node._netid] > 1 + min_hops[link.tail._netid] or link.head._netid == link.tail._netid:

                # Update estimate
                if link.head._netid != link.tail._netid:
                    min_hops[node._netid] = 1 + min_hops[link.tail._netid]

                # Add all the links going from the destination node to the queue
                # Also add the links to visited links set
                for customer in node.customers:
                    if customer._netid != link.tail._netid:
                        tovisit.append(Link(node, customer, Relationship.C))

                if node.path_type == 1 or node.path_type == 0:
                    for peer in node.peers:
                        if peer._netid != link.tail._netid:
                            tovisit.append(Link(node, peer, Relationship.R))
                    for provider in node.providers:
                        if provider._netid != link.tail._netid:
                            tovisit.append(Link(node, provider, Relationship.P))

            if tovisit:
                link = tovisit.popleft()
            else:
                return min_hops

    def __repr__(self):
        representation = 'Network:\n'
        for node in self._nodes:
            representation += '(' + \
                              'id=' + str(node.id) + ', ' + \
                              'customers=' + str(node.customers) + ', ' + \
                              'peers=' + str(node.peers) + ', ' + \
                              'providers=' + str(node.providers) + ', ' + \
                              'path_type=' + str(node.path_type) + ')\n'
        return representation
