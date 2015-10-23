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


