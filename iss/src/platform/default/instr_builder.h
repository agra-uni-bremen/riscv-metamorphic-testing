#pragma once
#include <cstdlib>
#include <unordered_map>

struct InstrBuilder {
    static uint32_t LUI(unsigned rd, unsigned U_imm);
    static uint32_t AUIPC(unsigned rd, unsigned U_imm);
    static uint32_t JAL(unsigned rd, int J_imm);
    static uint32_t JALR(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t _branch_format(unsigned rs1, unsigned rs2, int B_imm);
    static uint32_t BEQ(unsigned rs1, unsigned rs2, int B_imm);
    static uint32_t BNE(unsigned rs1, unsigned rs2, int B_imm);
    static uint32_t BLT(unsigned rs1, unsigned rs2, int B_imm);
    static uint32_t BGE(unsigned rs1, unsigned rs2, int B_imm);
    static uint32_t BLTU(unsigned rs1, unsigned rs2, int B_imm);
    static uint32_t BGEU(unsigned rs1, unsigned rs2, int B_imm);
    static uint32_t LB(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t LH(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t LW(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t LBU(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t LHU(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t SB(unsigned rs2, unsigned rs1, int S_imm);
    static uint32_t SH(unsigned rs2, unsigned rs1, int S_imm);
    static uint32_t SW(unsigned rs2, unsigned rs1, int S_imm);
    static uint32_t ADDI(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t SLTI(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t SLTIU(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t XORI(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t ORI(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t ANDI(unsigned rd, unsigned rs1, int I_imm);
    static uint32_t SLLI(unsigned rd, unsigned rs1, unsigned shamt);
    static uint32_t SRLI(unsigned rd, unsigned rs1, unsigned shamt);
    static uint32_t SRAI(unsigned rd, unsigned rs1, unsigned shamt);
    static uint32_t ADD(unsigned rd, unsigned rs1, unsigned rs2);
    static uint32_t SUB(unsigned rd, unsigned rs1, unsigned rs2);
    static uint32_t SLL(unsigned rd, unsigned rs1, unsigned rs2);
    static uint32_t SLT(unsigned rd, unsigned rs1, unsigned rs2);
    static uint32_t SLTU(unsigned rd, unsigned rs1, unsigned rs2);
    static uint32_t XOR(unsigned rd, unsigned rs1, unsigned rs2);
    static uint32_t SRL(unsigned rd, unsigned rs1, unsigned rs2);
    static uint32_t SRA(unsigned rd, unsigned rs1, unsigned rs2);
    static uint32_t OR(unsigned rd, unsigned rs1, unsigned rs2);
    static uint32_t AND(unsigned rd, unsigned rs1, unsigned rs2);
};
