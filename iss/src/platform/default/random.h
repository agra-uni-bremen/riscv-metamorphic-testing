#pragma once
#include <cstdlib>
#include <unordered_map>

struct Random {
    unsigned operator()(unsigned n);
    int8_t byte();
    unsigned u_imm();
    int i_imm();
    int s_imm();
    int b_imm();
    int j_imm();
    uint32_t reg_val();
    uint32_t reg_val(unsigned reg);
    unsigned reg();
    unsigned non_zero_reg();
    unsigned unique_reg(std::initializer_list<unsigned> xs);
};
