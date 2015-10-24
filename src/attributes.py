from relationship import Relationship


class ASTypeAttr(object):

    def __init__(self, relationship=Relationship.NON):
        self._relationship = relationship

    @property
    def value(self):
        return self._relationship

    @value.setter
    def value(self, other):
        self._relationship = other

    def operation(self, link_type):
        return ASTypeAttr(Relationship.operation_table[link_type][self._relationship])

    def __eq__(self, other):
        """
        :type other: ASTypeAttr
        """
        return self._relationship == other._relationship

    def __ne__(self, other):
        """
        :type other: ASTypeAttr
        """
        return self._relationship != other._relationship

    def __lt__(self, other):
        """
        :type other: ASTypeAttr
        """
        return self._relationship < other._relationship

    def __gt__(self, other):
        """
        :type other: ASTypeAttr
        """
        return self._relationship > other._relationship

    def __repr__(self):
        if self._relationship == Relationship.SELF:
            return 'O'
        elif self._relationship == Relationship.C:
            return 'C'
        elif self._relationship == Relationship.R:
            return 'R'
        elif self._relationship == Relationship.P:
            return 'P'
        else:
            return 'NON'


class HopCountAttr(object):

    def __init__(self, relationship=Relationship.NON, hop_count=-1):
        self._relationship = relationship
        self._hop_count = hop_count

    @property
    def value(self):
        return self._relationship, self._hop_count

    @value.setter
    def value(self, relationship, hop_count):
        self._relationship = relationship
        self._hop_count = hop_count

    def operation(self, link_type):
        return HopCountAttr(Relationship.operation_table[link_type][self._relationship], self._hop_count + 1)

    def __eq__(self, other):
        """
        :type other: HopCountAttr
        """
        return self._relationship == other._relationship and self._hop_count == other._hop_count

    def __ne__(self, other):
        """
        :type other: HopCountAttr
        """
        return self._relationship != other._relationship and self._hop_count != other._hop_count

    def __lt__(self, other):
        """
        :type other: HopCountAttr
        """
        comparison = self._relationship - other._relationship
        if comparison == 0:
            comparison = self._hop_count - other._hop_count

        return comparison < 0

    def __gt__(self, other):
        """
        :type other: HopCountAttr
        """
        comparison = self._relationship - other._relationship
        if comparison == 0:
            comparison = self._hop_count - other._hop_count

        return comparison > 0

    def __repr__(self):
        if self._relationship == Relationship.SELF:
            return 'O, ' + str(self._hop_count)
        elif self._relationship == Relationship.C:
            return 'C, ' + str(self._hop_count)
        elif self._relationship == Relationship.R:
            return 'R, ' + str(self._hop_count)
        elif self._relationship == Relationship.P:
            return 'P, ' + str(self._hop_count)
        else:
            return 'NON, ' + str(self._hop_count)
