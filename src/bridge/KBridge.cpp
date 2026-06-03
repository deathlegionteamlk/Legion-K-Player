#include "bridge/KBridge.hpp"
#include <iostream>
KBridge::KBridge() {}
void KBridge::sync() {}
void KBridge::dispatch(uint32_t syscall_id) {
    std::cout << "K_BRIDGE: Dispatching syscall " << syscall_id << std::endl;
}
