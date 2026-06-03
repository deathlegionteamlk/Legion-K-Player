#ifndef KENGINE_HPP
#define KENGINE_HPP

#include <vector>
#include <cstdint>
#include <iostream>
#include <stack>

enum class OpCode : uint8_t {
    HALT = 0x00,
    LDI  = 0x01,
    MOV  = 0x02,
    ADD  = 0x03,
    SUB  = 0x04,
    MUL  = 0x05,
    DIV  = 0x06,
    JMP  = 0x07,
    JZ   = 0x08,
    JNZ  = 0x09,
    PUSH = 0x0A,
    POP  = 0x0B,
    CALL = 0x0C,
    RET  = 0x0D,
    PRT  = 0x0E,
    LD   = 0x0F,
    ST   = 0x10
};

struct Instruction {
    OpCode op;
    uint8_t r1;
    uint8_t r2;
    int32_t val;
};

class KEngine {
public:
    KEngine();
    void loadProgram(const std::vector<Instruction>& program);
    void run();
    void step();
    bool isHalted() const;
    int32_t getRegister(uint8_t reg) const;
    void setRegister(uint8_t reg, int32_t value);
    void reset();

private:
    int32_t registers[16];
    int32_t memory[1024];
    uint32_t pc;
    bool halted;
    std::vector<Instruction> code;
    std::stack<uint32_t> callStack;
};

#endif
