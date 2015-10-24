from node import Node
from relationship import Relationship


class Link(object):

    def __init__(self, tail: Node, head: Node, type: Relationship):
        self.tail = tail
        self.head = head
        self.type = type

    def __repr__(self):
        return str(self.type) + ': ' + str(self.tail) + '->' + str(self.head)