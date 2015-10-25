
class Relationship(object):
    SELF = 0    # it self relationship
    C = 1       # customer-provider relationship
    R = 2       # peer-peer relationship
    P = 3       # provider-customer relationship
    NON = 4     # no relationship

    operation_table = [
        [SELF, SELF, SELF, SELF, SELF],
        [P, P, P, P, NON],
        [R, R, NON, NON, NON],
        [C, C, NON, NON, NON],
        [NON, NON, NON, NON, NON]
    ]


class PathCounter(object):

    def __init__(self):
        self._count = [0, 0, 0, 0]

    def increment(self, path_type):
        if path_type == Relationship.SELF:
            self._count[Relationship.C - 1] += 1
        else:
            self._count[path_type - 1] += 1

    def decrement(self, path_type):
        if path_type == Relationship.SELF:
            self._count[Relationship.C - 1] -= 1
        else:
            self._count[path_type - 1] -= 1

    def count(self, path_type):
        if path_type == Relationship.SELF:
            return self._count[Relationship.C - 1]
        else:
            return self._count[path_type - 1]

    def __repr__(self):
        return '[customer=%d, peer=%d, provider=%d, unusable=%d]' % (self._count[0], self._count[1],
                                                                     self._count[2], self._count[3])
