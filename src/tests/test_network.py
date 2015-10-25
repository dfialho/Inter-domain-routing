from network import Network
from relationship import Relationship


def test_algorithms(network):
    for node in network._nodes:
        print("ASType Destination=%d" % node.id)
        network.algorithm_astype(node.id)
        print(network)

    for node in network._nodes:
        print("HopCount Destination=%d" % node.id)
        network.algorithm_hop_count(node.id)
        print(network)

network = Network()

network.add_link(1, 2, Relationship.R)
network.add_link(2, 1, Relationship.R)
network.add_link(1, 3, Relationship.C)
network.add_link(3, 1, Relationship.P)
network.add_link(1, 4, Relationship.C)
network.add_link(4, 1, Relationship.P)
network.add_link(2, 4, Relationship.C)
network.add_link(4, 2, Relationship.P)
network.add_link(2, 5, Relationship.C)
network.add_link(5, 2, Relationship.P)

print("Original")
print(network)

print("TEST 1")
test_algorithms(network)

print(network.count_path())

print("TEST 2")
network.add_link(8, 5, Relationship.C)
network.add_link(5, 8, Relationship.P)
test_algorithms(network)

print(network.count_path())
