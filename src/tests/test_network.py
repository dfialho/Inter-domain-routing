from network import Network
from relationship import Relationship

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

print("ASType Destination=5")
network.algorithm_astype(5)
print(network)

print("ASType Destination=4")
network.algorithm_astype(4)
print(network)

print("ASType Destination=3")
network.algorithm_astype(3)
print(network)

print("ASType Destination=2")
network.algorithm_astype(2)
print(network)

print("ASType Destination=1")
network.algorithm_astype(1)
print(network)

print()

print("HopCount Destination=5")
network.algorithm_hop_count(5)
print(network)

print("HopCount Destination=4")
network.algorithm_hop_count(4)
print(network)

print("HopCount Destination=3")
network.algorithm_hop_count(3)
print(network)

print("HopCount Destination=2")
network.algorithm_hop_count(2)
print(network)

print("HopCount Destination=1")
network.algorithm_hop_count(1)
print(network)