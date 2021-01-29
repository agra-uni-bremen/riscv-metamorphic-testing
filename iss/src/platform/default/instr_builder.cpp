#include "instr_builder.h"

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