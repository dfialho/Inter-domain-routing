from network import Network
import time

t = time.time()
net = Network.from_file("testfiles/BIGDATA.txt")
net.find_routes(3)
hops = net.get_hops(3)
elapsed = time.time() - t

print(elapsed)

for key in hops.keys():
    print(str(key) + ' ' + str(hops[key]))

print()
all_paths = net.statistics_connections()
for connection in all_paths.keys():
    print(str(connection) + ' ' + str(all_paths[connection]))


print()
all_hops = net.statistics_hops(hops)
for x in range(len(all_hops)):
    print(str(x) + ' ' + str(all_hops[x]))