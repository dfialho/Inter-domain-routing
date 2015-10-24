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

print("Destination=5")
network.algorithm(5)
print(network)

print("Destination=4")
network.algorithm(4)
print(network)

print("Destination=3")
network.algorithm(3)
print(network)

print("Destination=2")
network.algorithm(2)
print(network)

print("Destination=1")
network.algorithm(1)
print(network)