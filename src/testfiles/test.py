from network import Network

net = Network.from_file("testfiles/hello.txt")
net.find_routes(1)

print(net)
print()
