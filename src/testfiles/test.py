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
