#include "code_builder.h"
#include "instr_builder.h"

constexpr static unsigned zero = 0;

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
void CodeBuilder::AUIPC(unsigned rd, unsigned imm) {
    code.push_back(InstrBuilder::LUI(rd, imm));
}
void CodeBuilder::JAL(unsigned rd, int imm) {
    code.push_back(InstrBuilder::JAL(rd, imm));
}
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
void CodeBuilder::LB(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::LB(rd, rs1, imm));
}
void CodeBuilder::LH(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::LH(rd, rs1, imm));
}
void CodeBuilder::LW(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::LW(rd, rs1, imm));
}
void CodeBuilder::LBU(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::LBU(rd, rs1, imm));
}
void CodeBuilder::LHU(unsigned rd, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::LHU(rd, rs1, imm));
}
void CodeBuilder::SB(unsigned rs2, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::SB(rs2, rs1, imm));
}
void CodeBuilder::SH(unsigned rs2, unsigned rs1, int imm) {
    code.push_back(InstrBuilder::SH(rs2, rs1, imm));
}
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
void CodeBuilder::MV(unsigned rd, unsigned rs) { 
    ADD(rd, rs, zero); 
}