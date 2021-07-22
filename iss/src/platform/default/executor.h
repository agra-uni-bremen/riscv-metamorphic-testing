#pragma once
#include <cstdlib>
#include <unordered_map>

#include "core/rv32/iss.h"
#include "memory.h"

constexpr static unsigned zero = 0;

enum class LoadInstr { LB,
                       LBU,
                       LH,
                       LHU,
                       LW };
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

struct Executor : public DefaultLoadStoreMemoryInterface {
    ISS &core;
    Random &random;
    CodeBuilder code;
    Executor(ISS &core, Random &random, RandomLazyMemory &mem);
    uint32_t load_instr(uint64_t addr);
    uint32_t run(unsigned rd = 0);
    uint32_t get_reg(unsigned idx);
    void check(bool cond);
};

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
