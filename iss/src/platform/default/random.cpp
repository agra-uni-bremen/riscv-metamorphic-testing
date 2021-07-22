#include <algorithm>
#include <cassert>
#include "random.h"

constexpr static unsigned zero = 0;
unsigned Random::operator()(unsigned n) {
    return rand() % n;
}
int8_t Random::byte() {
    return (rand() % 256) - 128;
}
unsigned Random::u_imm() {
    return rand() % 1048576;
}
int Random::i_imm() {
    return (rand() % 4096) - 2048;
}
int Random::s_imm() {
    return (rand() % 4096) - 2048;
}
int Random::b_imm() {
    return (rand() % 4096) << 1;
}
int Random::j_imm() {
    return (rand() % 1048576) << 1;
}
uint32_t Random::reg_val() {
    return rand() % 0xffffffff;
}
uint32_t Random::reg_val(unsigned reg) {
    if (reg == zero) return 0;
    return reg_val();
}
unsigned Random::reg() {
    return rand() % 32;
}
unsigned Random::non_zero_reg() {
    return (rand() % 31) + 1;
}
unsigned Random::unique_reg(std::initializer_list<unsigned> xs) {
    assert(xs.size() < 32);
    unsigned ans = reg();
    while (std::any_of(xs.begin(), xs.end(), [ans](unsigned i) { return i == ans; })) {
        ans = (ans + 1) % 32;
    }
    return ans;
}
#include <vector>
unsigned Random::unique_reg(std::vector<unsigned> xs) {
    assert(xs.size() < 32);
    unsigned ans = reg();
    while (std::any_of(xs.begin(), xs.end(), [ans](unsigned i) { return i == ans; })) {
        ans = (ans + 1) % 32;
    }
    return ans;
}