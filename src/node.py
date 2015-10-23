from relationship import Relationship


class Node(object):

    def __init__(self, id, netid=None):
        self.id = id
        self._netid = netid
        self._customers = []
        self._peers = []
        self._providers = []

    @property
    def customers(self):
        return self._customers

    @property
    def peers(self):
        return self._peers

    @property
    def providers(self):
        return self._providers

    @property
    def netid(self):
        return self._netid

    def add_link(self, node, relationship: Relationship):
        """
        :type node: Node
        """
        if relationship == Relationship.C:
            self._customers.append(node)
        elif relationship == Relationship.R:
            self._peers.append(node)
        elif relationship == Relationship.P:
            self._providers.append(node)

    def __repr__(self):
        return '(' + str(self.id) + ')'
