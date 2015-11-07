#include <iostream>
#include "../src/Network.h"

using namespace std;


int main() {

    Network network("/home/david/Development/IST/ADRC/Inter-domain-routing/tests/enunciado_ext1.txt");

    cout << "Initial Network" << endl;
    network.print();
    cout << endl;
}