#pragma once
#include <string>
#include <vector>
#include "random.h"
#include "executor.h"

using namespace rv32;
constexpr static unsigned zero = 0;
enum class LoadInstr { LB, LBU, LH, LHU, LW };

struct RuleCheckFailed : std::runtime_error {
    using runtime_error::runtime_error;
};
struct test_rule_if {
    virtual ~test_rule_if() {}
    virtual void randomize(Random &random) = 0;
    virtual void run(Executor &exec) = 0;
    virtual std::string to_string() = 0;
};
std::shared_ptr<test_rule_if> random_rule(Random &random);
struct ADD_Assoc : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2, rs3;
    uint32_t a, b, c;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
template <LoadInstr T>
struct LX_AddrId : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t a, b;
    int off1, off2;
    std::string to_string() override;
    void randomize(Random &random);
    void _LX(Executor &x, unsigned rd, unsigned rs, int off);
    void run(Executor &x);
};
template <unsigned N>
struct SX_LX_Id : public test_rule_if {
    static_assert(N == 1 || N == 2 || N == 4, "invalid memory width");
    unsigned rd, rs1, rs2;
    int32_t a, b;
    int off;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
struct LW_Combine2 : public test_rule_if {
    unsigned rd, rs1, rx, ry;
    uint32_t a;
    int off;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
struct LHU_Combine2 : public test_rule_if {
    unsigned rd, rs1, rx, ry;
    uint32_t a;
    int off;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
template <LoadInstr T>
struct LX_ExtCheck : public test_rule_if {
    unsigned rd, rs1, rx;
    uint32_t a;
    int off;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
template <unsigned N>
struct LXU_LX_Rel : public test_rule_if {
    static_assert(N == 1 || N == 2, "unsupported");
    unsigned rd, rs1, rx, ry;
    uint32_t a;
    int off;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
struct SW_RefCheck : public test_rule_if, public EmptyMemoryInterface {
    unsigned rs1, rs2;
    uint32_t a, b;
    uint64_t observed_addr;
    uint32_t observed_value;
    std::string to_string() override;
    void randomize(Random &random);
    void store_word(uint64_t addr, uint32_t value);
    void run(Executor &x);
};
struct ADD_Comm : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    uint32_t a, b;
    std::string to_string() override;
    void randomize(Random &random) override;
    void run(Executor &x) override;
};
struct ADD_Split : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2, rx, ry;
    uint32_t a, b;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
struct ADD_Split2 : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    uint32_t a, b, b_low, b_high;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
struct ADD_Change : public test_rule_if {
    unsigned rd, rs1, rs2;
    uint32_t a, b;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
struct SLLI_Meta1 : public test_rule_if {
    unsigned rs1, rd1, rd2;
    uint32_t a, b;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
struct SRLI_Meta1 : public test_rule_if {
    unsigned rs1, rd1, rd2;
    uint32_t a, b;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};
struct XOR_Meta1 : public test_rule_if {
    unsigned rd1, rd2, rs1;
    uint32_t a, b, c;
    std::string to_string() override;
    void randomize(Random &random);
    void run(Executor &x);
};


