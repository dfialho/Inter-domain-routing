
class Relationship:
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

    @staticmethod
    def operation(link_type, path_type):
        return Relationship.operation_table[link_type][path_type]
