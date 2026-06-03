#include "network/KNetwork.hpp"
#include <iostream>
KNetwork::KNetwork() {}
void KNetwork::connect(std::string host) {
    std::cout << "K_NET: Connecting to " << host << std::endl;
}
void KNetwork::stream() {}
