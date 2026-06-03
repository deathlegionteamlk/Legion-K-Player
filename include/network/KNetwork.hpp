#ifndef K_NETWORK_HPP
#define K_NETWORK_HPP
#include "core/Types.hpp"
class KNetwork {
public:
    KNetwork();
    void connect(std::string host);
    void stream();
};
#endif
