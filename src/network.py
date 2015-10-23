from node import Node


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

    def __repr__(self):
        representation = 'Network:\n'
        for node in self._nodes:
            representation += '(' + \
                              'id=' + str(node.id) + ', ' + \
                              'customers=' + str(node.customers) + ', ' + \
                              'peers=' + str(node.peers) + ', ' + \
                              'providers=' + str(node.providers) + ')\n'
        return representation
