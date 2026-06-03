#ifndef K_BRIDGE_HPP
#define K_BRIDGE_HPP
#include "core/Types.hpp"
class KBridge {
public:
    KBridge();
    void sync();
    void dispatch(uint32_t syscall_id);
};
#endif
