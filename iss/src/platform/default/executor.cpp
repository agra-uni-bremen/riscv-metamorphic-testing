#include "executor.h"

#include "memory.h"
#include "tests.h"

/* Executor */
Executor::Executor(ISS &core, Random &random, RandomLazyMemory &mem)
    : DefaultLoadStoreMemoryInterface(mem), core(core), random(random) {
    core.instr_mem = this;
    core.mem = this;
}
uint32_t Executor::load_instr(uint64_t addr) {
    return code.next();
}
uint32_t Executor::run(unsigned rd) {
    assert(code.has_next());
    while (code.has_next()) {
        core.run_step();
    }
    code.clear();
    return core.regs[rd];
}
uint32_t Executor::get_reg(unsigned idx) {
    return core.regs[idx];
}
void Executor::check(bool cond) {
    if (!cond) throw RuleCheckFailed("ERROR: rule check failed");
}

/* InstrBuilder */
uint32_t InstrBuilder::LUI(unsigned rd, unsigned U_imm) {
    return ((U_imm & 1048575) << 12) | ((rd & 0x1f) << 7) | 0b0110111;
}
uint32_t InstrBuilder::AUIPC(unsigned rd, unsigned U_imm) {
    return ((U_imm & 1048575) << 12) | ((rd & 0x1f) << 7) | 0b0010111;
}
uint32_t InstrBuilder::JAL(unsigned rd, int J_imm) {
    return 0b1101111 | ((rd & 0x1f) << 7) | ((J_imm & (0b11111111 << 12)) | ((J_imm & (1 << 11)) << 9) | ((J_imm & 0b11111111110) << 20) | ((J_imm & (1 << 20)) << 11));
}
uint32_t InstrBuilder::JALR(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 103;
}
uint32_t InstrBuilder::_branch_format(unsigned rs1, unsigned rs2, int B_imm) {
    return ((((B_imm & 0b11110) << 7) | ((B_imm & (1 << 11)) >> 4)) | (((B_imm & (0b111111 << 5)) << 20) | ((B_imm & (1 << 12)) << 19))) | ((rs1 & 0x1f) << 15) | ((rs2 & 0x1f) << 20) | 0b1100011;
}
uint32_t InstrBuilder::BEQ(unsigned rs1, unsigned rs2, int B_imm) {
    return _branch_format(rs1, rs2, B_imm) | (0b000 << 12);
}
uint32_t InstrBuilder::BNE(unsigned rs1, unsigned rs2, int B_imm) {
    return _branch_format(rs1, rs2, B_imm) | (0b001 << 12);
}
uint32_t InstrBuilder::BLT(unsigned rs1, unsigned rs2, int B_imm) {
    return _branch_format(rs1, rs2, B_imm) | (0b100 << 12);
}
uint32_t InstrBuilder::BGE(unsigned rs1, unsigned rs2, int B_imm) {
    return _branch_format(rs1, rs2, B_imm) | (0b101 << 12);
}
uint32_t InstrBuilder::BLTU(unsigned rs1, unsigned rs2, int B_imm) {
    return _branch_format(rs1, rs2, B_imm) | (0b110 << 12);
}
uint32_t InstrBuilder::BGEU(unsigned rs1, unsigned rs2, int B_imm) {
    return _branch_format(rs1, rs2, B_imm) | (0b111 << 12);
}
uint32_t InstrBuilder::LB(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 0b0000011 | (0b000 << 12);
}
uint32_t InstrBuilder::LH(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 0b0000011 | (0b001 << 12);
}
uint32_t InstrBuilder::LW(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 0b0000011 | (0b010 << 12);
}
uint32_t InstrBuilder::LBU(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 0b0000011 | (0b100 << 12);
}
uint32_t InstrBuilder::LHU(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 0b0000011 | (0b101 << 12);
}
uint32_t InstrBuilder::SB(unsigned rs2, unsigned rs1, int S_imm) {
    return (((S_imm & 0b11111) << 7) | ((S_imm & (0b1111111 << 5)) << 20)) | ((rs1 & 0x1f) << 15) | ((rs2 & 0x1f) << 20) | 0b0100011 | (0b000 << 12);
}
uint32_t InstrBuilder::SH(unsigned rs2, unsigned rs1, int S_imm) {
    return (((S_imm & 0b11111) << 7) | ((S_imm & (0b1111111 << 5)) << 20)) | ((rs1 & 0x1f) << 15) | ((rs2 & 0x1f) << 20) | 0b0100011 | (0b001 << 12);
}
uint32_t InstrBuilder::SW(unsigned rs2, unsigned rs1, int S_imm) {
    return (((S_imm & 0b11111) << 7) | ((S_imm & (0b1111111 << 5)) << 20)) | ((rs1 & 0x1f) << 15) | ((rs2 & 0x1f) << 20) | 0b0100011 | (0b010 << 12);
}
uint32_t InstrBuilder::ADDI(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011;
}
uint32_t InstrBuilder::SLTI(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b010 << 12);
}
uint32_t InstrBuilder::SLTIU(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b011 << 12);
}
uint32_t InstrBuilder::XORI(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b100 << 12);
}
uint32_t InstrBuilder::ORI(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b110 << 12);
}
uint32_t InstrBuilder::ANDI(unsigned rd, unsigned rs1, int I_imm) {
    return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b111 << 12);
}
uint32_t InstrBuilder::SLLI(unsigned rd, unsigned rs1, unsigned shamt) {
    return ((shamt & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b001 << 12);
}
uint32_t InstrBuilder::SRLI(unsigned rd, unsigned rs1, unsigned shamt) {
    return ((shamt & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b101 << 12);
}
uint32_t InstrBuilder::SRAI(unsigned rd, unsigned rs1, unsigned shamt) {
    return ((shamt & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b101 << 12) | (0b0100000 << 25);
}
uint32_t InstrBuilder::ADD(unsigned rd, unsigned rs1, unsigned rs2) {
    return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011;
}
uint32_t InstrBuilder::SUB(unsigned rd, unsigned rs1, unsigned rs2) {
    return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b0100000 << 25);
}
uint32_t InstrBuilder::SLL(unsigned rd, unsigned rs1, unsigned rs2) {
    return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b001 << 12);
}
uint32_t InstrBuilder::SLT(unsigned rd, unsigned rs1, unsigned rs2) {
    return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b010 << 12);
}
uint32_t InstrBuilder::SLTU(unsigned rd, unsigned rs1, unsigned rs2) {
    return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b011 << 12);
}
uint32_t InstrBuilder::XOR(unsigned rd, unsigned rs1, unsigned rs2) {
    return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b100 << 12);
}
uint32_t InstrBuilder::SRL(unsigned rd, unsigned rs1, unsigned rs2) {
    return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b101 << 12);
}
uint32_t InstrBuilder::SRA(unsigned rd, unsigned rs1, unsigned rs2) {
    return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b101 << 12) | (0b0100000 << 25);
}
uint32_t InstrBuilder::OR(unsigned rd, unsigned rs1, unsigned rs2) {
    return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b110 << 12);
}
uint32_t InstrBuilder::AND(unsigned rd, unsigned rs1, unsigned rs2) {
    return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b111 << 12);
}

/* CodeBuilder */
void CodeBuilder::clear() {
    code.clear();
    idx = 0;
}
uint32_t CodeBuilder::next() {
    return code[idx++];
}
bool CodeBuilder::has_next() {
    return idx < code.size();
}
void CodeBuilder::LUI(unsigned rd, unsigned imm) {
    code.push_back(InstrBuilder::LUI(rd, imm));
}
/* Add upper immediate to PC.
   rd: register, imm[U]: offset */
void CodeBuilder::AUIPC(unsigned rd, unsigned imm) {
    code.push_back(InstrBuilder::AUIPC(rd, imm));
}
void CodeBuilder::JAL(unsigned rd, int imm) {
    code.push_back(InstrBuilder::JAL(rd, imm));
}
/* rd: stores pc, imm[I]: */
void CodeBuilder::JALR(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::JALR(rd, rs1, imm));
}
void CodeBuilder::BEQ(unsigned rs1, unsigned rs2, int imm) {
    code.push_back(InstrBuilder::BEQ(rs1, rs2, imm));
}
void CodeBuilder::BNE(unsigned rs1, unsigned rs2, int imm) {
    code.push_back(InstrBuilder::BNE(rs1, rs2, imm));
}
void CodeBuilder::BLT(unsigned rs1, unsigned rs2, int imm) {
    code.push_back(InstrBuilder::BLT(rs1, rs2, imm));
}
void CodeBuilder::BGE(unsigned rs1, unsigned rs2, int imm) {
    code.push_back(InstrBuilder::BGE(rs1, rs2, imm));
}
void CodeBuilder::BLTU(unsigned rs1, unsigned rs2, int imm) {
    code.push_back(InstrBuilder::BLTU(rs1, rs2, imm));
}
void CodeBuilder::BGEU(unsigned rs1, unsigned rs2, int imm) {
    code.push_back(InstrBuilder::BGEU(rs1, rs2, imm));
}
/* rd: value, rs1: address, imm[I]: offset */
void CodeBuilder::LB(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::LB(rd, rs1, imm));
}
/* rd: value, rs1: address, imm[I]: offset */
void CodeBuilder::LH(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::LH(rd, rs1, imm));
}
/* rd: value, rs1: address, imm[I]: offset */
void CodeBuilder::LW(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::LW(rd, rs1, imm));
}
/* rd: value, rs1: address, imm[I]: offset */
void CodeBuilder::LBU(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::LBU(rd, rs1, imm));
}
/* rd: value, rs1: address, imm[I]: offset */
void CodeBuilder::LHU(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::LHU(rd, rs1, imm));
}
/* rs2: value, rs1: address, imm[S]: offset */
void CodeBuilder::SB(unsigned rs2, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::SB(rs2, rs1, imm));
}
/* rs2: value, rs1: address, imm[S]: offset */
void CodeBuilder::SH(unsigned rs2, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::SH(rs2, rs1, imm));
}
/* rs2: value, rs1: address, imm[S]: offset */
void CodeBuilder::SW(unsigned rs2, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::SW(rs2, rs1, imm));
}
void CodeBuilder::ADDI(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::ADDI(rd, rs1, imm));
}
void CodeBuilder::SLTI(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::SLTI(rd, rs1, imm));
}
void CodeBuilder::SLTIU(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::SLTIU(rd, rs1, imm));
}
/* rd: dest, rs1: op1, imm[I]: op2 */
void CodeBuilder::XORI(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::XORI(rd, rs1, imm));
}
void CodeBuilder::ORI(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::ORI(rd, rs1, imm));
}
void CodeBuilder::ANDI(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::ANDI(rd, rs1, imm));
}
void CodeBuilder::SLLI(unsigned rd, unsigned rs1, unsigned shamt) {
    code.push_back(InstrBuilder::SLLI(rd, rs1, shamt));
}
void CodeBuilder::SRLI(unsigned rd, unsigned rs1, unsigned shamt) {
    code.push_back(InstrBuilder::SRLI(rd, rs1, shamt));
}
void CodeBuilder::SRAI(unsigned rd, unsigned rs1, unsigned shamt) {
    code.push_back(InstrBuilder::SRAI(rd, rs1, shamt));
}
void CodeBuilder::ADD(unsigned rd, unsigned rs1, unsigned rs2) {
    code.push_back(InstrBuilder::ADD(rd, rs1, rs2));
}
void CodeBuilder::SUB(unsigned rd, unsigned rs1, unsigned rs2) {
    code.push_back(InstrBuilder::SUB(rd, rs1, rs2));
}
void CodeBuilder::SLL(unsigned rd, unsigned rs1, unsigned rs2) {
    code.push_back(InstrBuilder::SLL(rd, rs1, rs2));
}
void CodeBuilder::SLT(unsigned rd, unsigned rs1, unsigned rs2) {
    code.push_back(InstrBuilder::SLT(rd, rs1, rs2));
}
void CodeBuilder::SLTU(unsigned rd, unsigned rs1, unsigned rs2) {
    code.push_back(InstrBuilder::SLTU(rd, rs1, rs2));
}
void CodeBuilder::XOR(unsigned rd, unsigned rs1, unsigned rs2) {
    code.push_back(InstrBuilder::XOR(rd, rs1, rs2));
}
void CodeBuilder::SRL(unsigned rd, unsigned rs1, unsigned rs2) {
    code.push_back(InstrBuilder::SRL(rd, rs1, rs2));
}
void CodeBuilder::SRA(unsigned rd, unsigned rs1, unsigned rs2) {
    code.push_back(InstrBuilder::SRA(rd, rs1, rs2));
}
void CodeBuilder::OR(unsigned rd, unsigned rs1, unsigned rs2) {
    code.push_back(InstrBuilder::OR(rd, rs1, rs2));
}
void CodeBuilder::AND(unsigned rd, unsigned rs1, unsigned rs2) {
    code.push_back(InstrBuilder::AND(rd, rs1, rs2));
}
/* RV32I pseudo-instructions */
/* Load immediate */
void CodeBuilder::LI(unsigned rd, int imm) {
    if (imm >= -2048 && imm <= 2047) {
        ADDI(rd, zero, imm);
    } else {
        auto x = imm & 4095;
        if (x > 2047) {
            x -= 4096;
            LUI(rd, (imm >> 12) + 1);
        } else {
            LUI(rd, imm >> 12);
        }
        ADDI(rd, rd, x);
    }
}
/* Move */
void CodeBuilder::MV(unsigned rd, unsigned rs) {
    ADD(rd, rs, zero);
}
