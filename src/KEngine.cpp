#include "KEngine.hpp"

KEngine::KEngine() {
    reset();
}

void KEngine::reset() {
    for (int i = 0; i < 16; ++i) registers[i] = 0;
    for (int i = 0; i < 1024; ++i) memory[i] = 0;
    pc = 0;
    halted = false;
    while(!callStack.empty()) callStack.pop();
}

void KEngine::loadProgram(const std::vector<Instruction>& program) {
    code = program;
    pc = 0;
    halted = false;
}

void KEngine::run() {
    while (!halted && pc < code.size()) {
        step();
    }
}

void KEngine::step() {
    if (halted || pc >= code.size()) return;

    Instruction inst = code[pc++];
    switch (inst.op) {
        case OpCode::HALT:
            halted = true;
            break;
        case OpCode::LDI:
            if (inst.r1 < 16) registers[inst.r1] = inst.val;
            break;
        case OpCode::MOV:
            if (inst.r1 < 16 && inst.r2 < 16) registers[inst.r1] = registers[inst.r2];
            break;
        case OpCode::ADD:
            if (inst.r1 < 16 && inst.r2 < 16) registers[inst.r1] += registers[inst.r2];
            break;
        case OpCode::SUB:
            if (inst.r1 < 16 && inst.r2 < 16) registers[inst.r1] -= registers[inst.r2];
            break;
        case OpCode::MUL:
            if (inst.r1 < 16 && inst.r2 < 16) registers[inst.r1] *= registers[inst.r2];
            break;
        case OpCode::DIV:
            if (inst.r1 < 16 && inst.r2 < 16 && registers[inst.r2] != 0) registers[inst.r1] /= registers[inst.r2];
            break;
        case OpCode::JMP:
            pc = inst.val;
            break;
        case OpCode::JZ:
            if (inst.r1 < 16 && registers[inst.r1] == 0) pc = inst.val;
            break;
        case OpCode::JNZ:
            if (inst.r1 < 16 && registers[inst.r1] != 0) pc = inst.val;
            break;
        case OpCode::PUSH:
            if (inst.r1 < 16) callStack.push(registers[inst.r1]);
            break;
        case OpCode::POP:
            if (inst.r1 < 16 && !callStack.empty()) {
                registers[inst.r1] = callStack.top();
                callStack.pop();
            }
            break;
        case OpCode::CALL:
            callStack.push(pc);
            pc = inst.val;
            break;
        case OpCode::RET:
            if (!callStack.empty()) {
                pc = callStack.top();
                callStack.pop();
            }
            break;
        case OpCode::PRT:
            if (inst.r1 < 16) std::cout << "DEBUG_VAL: " << registers[inst.r1] << std::endl;
            break;
        case OpCode::LD:
            if (inst.r1 < 16 && inst.val >= 0 && inst.val < 1024) registers[inst.r1] = memory[inst.val];
            break;
        case OpCode::ST:
            if (inst.r1 < 16 && inst.val >= 0 && inst.val < 1024) memory[inst.val] = registers[inst.r1];
            break;
    }
}

bool KEngine::isHalted() const {
    return halted;
}

int32_t KEngine::getRegister(uint8_t reg) const {
    return reg < 16 ? registers[reg] : 0;
}

void KEngine::setRegister(uint8_t reg, int32_t value) {
    if (reg < 16) registers[reg] = value;
}
