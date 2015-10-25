from collections import deque
from attributes import ASTypeAttr, HopCountAttr
from link import Link
from node import Node
from relationship import Relationship, PathCounter
from collections import defaultdict


class Network(object):

    def __init__(self):
        self._nodes = []
        self._ids = {}
        self._netid_count = -1

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

    def algorithm_astype(self, dest_id):
        for node in self._nodes:
            node.path_type = ASTypeAttr()

        self._algorithm(dest_id)

    def algorithm_hop_count(self, dest_id):
        for node in self._nodes:
            node.path_type = HopCountAttr()

        self._algorithm(dest_id)

    def _algorithm(self, dest_id, path_counter=None, hop_count_counter=None):

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

            path_type = link.tail.path_type.operation(link.type)
            if path_type < node.path_type:
                if path_counter:
                    path_counter.decrement(node.path_type.value[0])
                    if node.path_type.value[1] > 0:
                        hop_count_counter[node.path_type.value[1]] -= 1

                node.path_type = path_type

                if path_counter:
                    path_counter.increment(node.path_type.value[0])
                    hop_count_counter[node.path_type.value[1]] += 1

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

    def count_path(self):
        path_counter = PathCounter()
        hop_count_counter = defaultdict(int)

        for dest_node in self._nodes:
            for node in self._nodes:
                node.path_type = HopCountAttr()
                path_counter.increment(Relationship.NON)

            self._algorithm(dest_node.id, path_counter, hop_count_counter)

        return path_counter, hop_count_counter

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
