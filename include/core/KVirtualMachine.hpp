#ifndef K_VIRTUAL_MACHINE_HPP
#define K_VIRTUAL_MACHINE_HPP
#include "Types.hpp"
#include <stack>
#include <map>
enum class K_OP : uint8_t {
    SYS_HALT = 0x00,
    REG_LOAD = 0x01,
    REG_MOVE = 0x02,
    ALU_ADD  = 0x03,
    ALU_SUB  = 0x04,
    ALU_MUL  = 0x05,
    ALU_DIV  = 0x06,
    ALU_AND  = 0x07,
    ALU_OR   = 0x08,
    FLO_JMP  = 0x09,
    FLO_JZ   = 0x0A,
    FLO_JNZ  = 0x0B,
    STK_PUSH = 0x0C,
    STK_POP  = 0x0D,
    SYS_CALL = 0x0E,
    SYS_RET  = 0x0F,
    MEM_LD   = 0x10,
    MEM_ST   = 0x11,
    OUT_PRT  = 0x12
};
struct K_INS {
    K_OP op;
    k_reg r1;
    k_reg r2;
    k_word imm;
};
class KVirtualMachine {
public:
    KVirtualMachine();
    void boot(const std::vector<K_INS>& image);
    void cycle();
    void pulse();
    bool alive() const;
    void flush();
    k_word read_reg(k_reg r) const;
    void write_reg(k_reg r, k_word v);
private:
    k_word regs[16];
    k_word ram[4096];
    k_addr pc;
    bool active;
    std::vector<K_INS> rom;
    std::stack<k_addr> frames;
};
#endif
