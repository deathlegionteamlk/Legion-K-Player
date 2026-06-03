#include "core/KVirtualMachine.hpp"
#include <iostream>
KVirtualMachine::KVirtualMachine() {
    flush();
}
void KVirtualMachine::flush() {
    for (int i = 0; i < 16; ++i) regs[i] = 0;
    for (int i = 0; i < 4096; ++i) ram[i] = 0;
    pc = 0;
    active = false;
    while(!frames.empty()) frames.pop();
}
void KVirtualMachine::boot(const std::vector<K_INS>& image) {
    rom = image;
    pc = 0;
    active = true;
}
void KVirtualMachine::cycle() {
    while (active && pc < rom.size()) {
        pulse();
    }
}
void KVirtualMachine::pulse() {
    if (!active || pc >= rom.size()) return;
    K_INS ins = rom[pc++];
    switch (ins.op) {
        case K_OP::SYS_HALT: active = false; break;
        case K_OP::REG_LOAD: if (ins.r1 < 16) regs[ins.r1] = ins.imm; break;
        case K_OP::REG_MOVE: if (ins.r1 < 16 && ins.r2 < 16) regs[ins.r1] = regs[ins.r2]; break;
        case K_OP::ALU_ADD:  if (ins.r1 < 16 && ins.r2 < 16) regs[ins.r1] += regs[ins.r2]; break;
        case K_OP::ALU_SUB:  if (ins.r1 < 16 && ins.r2 < 16) regs[ins.r1] -= regs[ins.r2]; break;
        case K_OP::ALU_MUL:  if (ins.r1 < 16 && ins.r2 < 16) regs[ins.r1] *= regs[ins.r2]; break;
        case K_OP::ALU_DIV:  if (ins.r1 < 16 && ins.r2 < 16 && regs[ins.r2] != 0) regs[ins.r1] /= regs[ins.r2]; break;
        case K_OP::ALU_AND:  if (ins.r1 < 16 && ins.r2 < 16) regs[ins.r1] &= regs[ins.r2]; break;
        case K_OP::ALU_OR:   if (ins.r1 < 16 && ins.r2 < 16) regs[ins.r1] |= regs[ins.r2]; break;
        case K_OP::FLO_JMP:  pc = ins.imm; break;
        case K_OP::FLO_JZ:   if (ins.r1 < 16 && regs[ins.r1] == 0) pc = ins.imm; break;
        case K_OP::FLO_JNZ:  if (ins.r1 < 16 && regs[ins.r1] != 0) pc = ins.imm; break;
        case K_OP::STK_PUSH: if (ins.r1 < 16) frames.push(regs[ins.r1]); break;
        case K_OP::STK_POP:  if (ins.r1 < 16 && !frames.empty()) { regs[ins.r1] = frames.top(); frames.pop(); } break;
        case K_OP::SYS_CALL: frames.push(pc); pc = ins.imm; break;
        case K_OP::SYS_RET:  if (!frames.empty()) { pc = frames.top(); frames.pop(); } break;
        case K_OP::MEM_LD:   if (ins.r1 < 16 && ins.imm >= 0 && ins.imm < 4096) regs[ins.r1] = ram[ins.imm]; break;
        case K_OP::MEM_ST:   if (ins.r1 < 16 && ins.imm >= 0 && ins.imm < 4096) ram[ins.imm] = regs[ins.r1]; break;
        case K_OP::OUT_PRT:  if (ins.r1 < 16) std::cout << "K_OUT: " << regs[ins.r1] << std::endl; break;
    }
}
bool KVirtualMachine::alive() const { return active; }
k_word KVirtualMachine::read_reg(k_reg r) const { return r < 16 ? regs[r] : 0; }
void KVirtualMachine::write_reg(k_reg r, k_word v) { if (r < 16) regs[r] = v; }
