#pragma once
#include <cstdlib>
#include <unordered_map>
#include <vector>

struct CodeBuilder {
    std::vector<uint32_t> code;
    unsigned idx = 0;

    void clear();
    uint32_t next();
    bool has_next();

    /* RV32I instructions */
    void LUI(unsigned rd, unsigned imm);
    void AUIPC(unsigned rd, unsigned imm);
    void JAL(unsigned rd, int imm);
    void JALR(unsigned rd, unsigned rs1, int imm);
    void BEQ(unsigned rs1, unsigned rs2, int imm);
    void BNE(unsigned rs1, unsigned rs2, int imm);
    void BLT(unsigned rs1, unsigned rs2, int imm);
    void BGE(unsigned rs1, unsigned rs2, int imm);
    void BLTU(unsigned rs1, unsigned rs2, int imm);
    void BGEU(unsigned rs1, unsigned rs2, int imm);
    void LB(unsigned rd, unsigned rs1, int imm);
    void LH(unsigned rd, unsigned rs1, int imm);
    void LW(unsigned rd, unsigned rs1, int imm);
    void LBU(unsigned rd, unsigned rs1, int imm);
    void LHU(unsigned rd, unsigned rs1, int imm);
    void SB(unsigned rs2, unsigned rs1, int imm);
    void SH(unsigned rs2, unsigned rs1, int imm);
    void SW(unsigned rs2, unsigned rs1, int imm);
    void ADDI(unsigned rd, unsigned rs1, int imm);
    void SLTI(unsigned rd, unsigned rs1, int imm);
    void SLTIU(unsigned rd, unsigned rs1, int imm);
    void XORI(unsigned rd, unsigned rs1, int imm);
    void ORI(unsigned rd, unsigned rs1, int imm);
    void ANDI(unsigned rd, unsigned rs1, int imm);
    void SLLI(unsigned rd, unsigned rs1, unsigned shamt);
    void SRLI(unsigned rd, unsigned rs1, unsigned shamt);
    void SRAI(unsigned rd, unsigned rs1, unsigned shamt);
    void ADD(unsigned rd, unsigned rs1, unsigned rs2);
    void SUB(unsigned rd, unsigned rs1, unsigned rs2);
    void SLL(unsigned rd, unsigned rs1, unsigned rs2);
    void SLT(unsigned rd, unsigned rs1, unsigned rs2);
    void SLTU(unsigned rd, unsigned rs1, unsigned rs2);
    void XOR(unsigned rd, unsigned rs1, unsigned rs2);
    void SRL(unsigned rd, unsigned rs1, unsigned rs2);
    void SRA(unsigned rd, unsigned rs1, unsigned rs2);
    void OR(unsigned rd, unsigned rs1, unsigned rs2);
    void AND(unsigned rd, unsigned rs1, unsigned rs2);
    /* RV32I pseudo-instructions */
    void LI(unsigned rd, int imm);
    void MV(unsigned rd, unsigned rs);
};
