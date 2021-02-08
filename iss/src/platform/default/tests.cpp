#include "tests.h"

#include <sstream>

#include "common.h"
#include "memory.h"

/* (a + b) + c == a + (b + c) */
struct ADD_Assoc : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2, rs3;
    uint32_t a, b, c;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2, &rs3);
        ATTRIBUTE(a, r.i_imm());
        ATTRIBUTE(b, r.i_imm());
        ATTRIBUTE(c, r.i_imm());

        x.code.LI(rs1, a);
        x.code.LI(rs2, b);
        x.code.ADD(rd1, rs1, rs2);
        x.code.LI(rs1, c);
        x.code.ADD(rd1, rd1, rs1);

        x.code.LI(rs1, b);
        x.code.LI(rs2, c);
        x.code.ADD(rd2, rs1, rs2);
        x.code.LI(rs1, a);
        x.code.ADD(rd2, rd2, rs1);

        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* (a + b) + c == a + (b + c) */
struct ADDI_Assoc : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2, rs3;
    uint32_t a, b, c;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2, &rs3);
        ATTRIBUTE(a, r.i_imm());
        ATTRIBUTE(b, r.i_imm());
        ATTRIBUTE(c, r.i_imm());

        x.code.LI(rs1, c);
        x.code.ADDI(rs1, rs1, a);
        x.code.ADDI(rd1, rs1, b);

        x.code.LI(rs1, a);
        x.code.ADDI(rs1, rs1, b);
        x.code.ADDI(rd2, rs1, c);

        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* */
template <LoadInstr T>
struct LX_AddrId : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t a, b;
    int off1, off2;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rs1, &rs2, &rd1, &rd2);
        ATTRIBUTE(a, r.reg_val(rs1));
        ATTRIBUTE(off1, align_memory_addr<GetAlignWidth<T>()>(a, r.i_imm()));
        ATTRIBUTE(off2, r.i_imm());

        x.code.LI(rs1, a);
        _LX(x, rd1, rs1, off1);

        x.code.ADDI(rs2, rs1, off1);
        x.code.ADDI(rd2, zero, off2);
        x.code.SUB(rs2, rs2, rd2);
        _LX(x, rd2, rs2, off2);

        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
    void _LX(Executor &x, unsigned rd, unsigned rs, int off) {
        if (T == LoadInstr::LB)
            x.code.LB(rd, rs, off);
        else if (T == LoadInstr::LBU)
            x.code.LBU(rd, rs, off);
        else if (T == LoadInstr::LH)
            x.code.LH(rd, rs, off);
        else if (T == LoadInstr::LHU)
            x.code.LHU(rd, rs, off);
        else if (T == LoadInstr::LW)
            x.code.LW(rd, rs, off);
        else {
            throw std::runtime_error("not implemented");
            ;
        }
    }
    std::string to_string() {
        return test_rule_if::to_string<T>();
    }
};
/* */
template <unsigned N>
struct SX_LX_Id : public test_rule_if {
    static_assert(N == 1 || N == 2 || N == 4, "invalid memory width");
    unsigned rd, rs1, rs2;
    int32_t a, b;
    int off;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.reg());
        ATTRIBUTE(rs2, r.reg());
        ATTRIBUTE(rd, r.unique_reg({zero}));
        ATTRIBUTE(a, r.reg_val(rs1));
        ATTRIBUTE(b, r.reg_val());
        ATTRIBUTE(off, align_memory_addr<N>(a, r.i_imm()));

        x.code.LI(rs2, b);
        x.code.LI(rs1, a);  // ensure that rs1 is aligned in case rs1==rs2
        if (N == 1) {
            x.code.SB(rs2, rs1, off);
            x.code.LBU(rd, rs1, off);
            x.code.ANDI(rs2, rs2, 0xff);
        } else if (N == 2) {
            x.code.SH(rs2, rs1, off);
            x.code.LHU(rd, rs1, off);
            x.code.SLLI(rs2, rs2, 16);
            x.code.SRLI(rs2, rs2, 16);
        } else if (N == 4) {
            x.code.SW(rs2, rs1, off);
            x.code.LW(rd, rs1, off);
        }
        x.run();
        x.check(x.get_reg(rd) == x.get_reg(rs2));
    }
};
/* */
struct LW_Combine2 : public test_rule_if {
    unsigned rd, rs1, rx, ry;
    uint32_t a;
    int off;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.unique_reg({zero}));
        ATTRIBUTE(rd, r.unique_reg({rs1, zero}));
        ATTRIBUTE(rx, r.unique_reg({rs1, rd, zero}));
        ATTRIBUTE(ry, r.unique_reg({rs1, rd, rx, zero}));
        ATTRIBUTE(a, r.reg_val(rs1));
        ATTRIBUTE(off, align_memory_addr<4>(a, r.i_imm()));

        x.code.LI(rs1, a);
        x.code.LW(rd, rs1, off);
        x.code.LHU(rx, rs1, off);
        x.code.ADDI(rs1, rs1, 2);
        x.code.LHU(ry, rs1, off);
        x.code.SLLI(ry, ry, 16);
        x.code.OR(rx, rx, ry);

        x.run();
        x.check(x.get_reg(rd) == x.get_reg(rx));
    }
};
/* */
struct LHU_Combine2 : public test_rule_if {
    unsigned rd, rs1, rx, ry;
    uint32_t a;
    int off;
    void run(Executor &x, Random &r) {
        attributes.clear();
        ATTRIBUTE(rs1, r.unique_reg({zero}));
        ATTRIBUTE(rd, r.unique_reg({rs1, zero}));
        ATTRIBUTE(rx, r.unique_reg({rs1, rd, zero}));
        ATTRIBUTE(ry, r.unique_reg({rs1, rd, rx, zero}));
        ATTRIBUTE(a, r.reg_val(rs1));
        ATTRIBUTE(off, align_memory_addr<2>(a, r.i_imm()));

        x.code.LI(rs1, a);
        x.code.LHU(rd, rs1, off);
        x.code.LBU(rx, rs1, off);
        x.code.ADDI(rs1, rs1, 1);
        x.code.LBU(ry, rs1, off);
        x.code.SLLI(ry, ry, 8);
        x.code.OR(rx, rx, ry);

        x.run();
        x.check(x.get_reg(rd) == x.get_reg(rx));
    }
};
/* */
template <LoadInstr T>
struct LX_ExtCheck : public test_rule_if {
    unsigned rd, rs1, rx;
    uint32_t a;
    int off;
    void run(Executor &x, Random &r) {
        attributes.clear();
        ATTRIBUTE(rs1, r.reg());
        ATTRIBUTE(rd, r.reg());
        ATTRIBUTE(rx, r.unique_reg({rd, zero}));
        ATTRIBUTE(a, r.reg_val(rs1));
        ATTRIBUTE(off, align_memory_addr<GetAlignWidth<T>()>(a, r.i_imm()));

        unsigned shamt = 16;
        if (T == LoadInstr::LB || T == LoadInstr::LBU) shamt = 8;

        x.code.LI(rs1, a);
        if (T == LoadInstr::LB)
            x.code.LB(rd, rs1, off);
        else if (T == LoadInstr::LBU)
            x.code.LBU(rd, rs1, off);
        else if (T == LoadInstr::LH)
            x.code.LH(rd, rs1, off);
        else if (T == LoadInstr::LHU)
            x.code.LHU(rd, rs1, off);
        else
            throw TraceableException("not supported");
        x.code.MV(rx, rd);
        x.code.SLLI(rx, rx, shamt);
        if (T == LoadInstr::LB || T == LoadInstr::LH)
            x.code.SRAI(rx, rx, shamt);
        else
            x.code.SRLI(rx, rx, shamt);
        x.run();
        x.check(x.get_reg(rd) == x.get_reg(rx));
    }
    std::string to_string() {
        return test_rule_if::to_string<T>();
    }
};
/* */
template <unsigned N>
struct LXU_LX_Rel : public test_rule_if {
    static_assert(N == 1 || N == 2, "unsupported");
    unsigned rd, rs1, rx, ry;
    uint32_t a;
    int off;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.reg());
        ATTRIBUTE(rd, r.unique_reg({rs1, zero}));
        ATTRIBUTE(rx, r.unique_reg({rs1, rd, zero}));
        ATTRIBUTE(ry, r.unique_reg({rs1, rd, rx, zero}));
        ATTRIBUTE(a, r.reg_val(rs1));
        ATTRIBUTE(off, align_memory_addr<N>(a, r.i_imm()));

        constexpr unsigned shamt = N == 1 ? 24 : 16;
        x.code.LI(rs1, a);
        if (N == 1) {
            x.code.LBU(rd, rs1, off);
            x.code.LB(rx, rs1, off);
        } else {
            assert(N == 2);
            x.code.LHU(rd, rs1, off);
            x.code.LH(rx, rs1, off);
        }
        x.code.SLLI(ry, rx, shamt);
        x.code.SRLI(ry, ry, shamt);

        x.run();
        x.check(x.get_reg(rd) <= x.get_reg(rx));
        x.check(x.get_reg(rd) == x.get_reg(ry));
    }
};
/* */
struct SW_RefCheck : public test_rule_if, public EmptyMemoryInterface {
    unsigned rs1, rs2;
    uint32_t a, b;
    uint64_t observed_addr;
    uint32_t observed_value;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.reg());
        ATTRIBUTE(rs2, r.reg());
        ATTRIBUTE(a, align_memory_addr<4>(r.reg_val(rs1)));
        if (rs1 == rs2) {
            ATTRIBUTE(b, a);
        } else {
            ATTRIBUTE(b, r.reg_val(rs2));
        }
        struct SwitchDataMemoryInterface {
            Executor &x;
            data_memory_if *old;
            SwitchDataMemoryInterface(Executor &x, data_memory_if *new_) : x(x) {
                old = x.core.mem;
                x.core.mem = new_;
            }
            ~SwitchDataMemoryInterface() { x.core.mem = old; }
        };
        SwitchDataMemoryInterface tmp_option(x, this);
        x.code.LI(rs2, b);
        x.code.LI(rs1, a);  // load rs1 after rs2 to ensure proper alignment (in
                            // case rs1==rs2)
        x.code.SW(rs2, rs1, 0);
        x.run();
        x.check(observed_addr == a);
        x.check(observed_value == b);
    }
};
/* */
struct ADD_Comm : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    uint32_t a, b;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.reg());
        ATTRIBUTE(rs2, r.reg());
        ATTRIBUTE(rd1, r.unique_reg({rs1, rs2, zero}));
        ATTRIBUTE(rd2, r.unique_reg({rd1, rs1, rs2, zero}));
        ATTRIBUTE(a, r.reg_val());
        ATTRIBUTE(b, r.reg_val());

        x.code.LI(rs1, a);
        x.code.LI(rs2, b);
        x.code.ADD(rd1, rs1, rs2);
        x.code.ADD(rd2, rs2, rs1);
        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* */
struct ADD_Split1 : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2, rx, ry;
    uint32_t a, b;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.reg());
        ATTRIBUTE(rs2, r.reg());
        ATTRIBUTE(rd1, r.unique_reg({rs1, rs2, zero}));
        ATTRIBUTE(rd2, r.unique_reg({rd1, rs1, rs2, zero}));
        ATTRIBUTE(rx, r.unique_reg({rd1, rd2, rs1, rs2, zero}));
        ATTRIBUTE(ry, r.unique_reg({rx, rd1, rd2, rs1, rs2, zero}));
        ATTRIBUTE(a, r.reg_val());
        ATTRIBUTE(b, r.reg_val());

        x.code.LI(rs1, a);
        x.code.LI(rs2, b);
        x.code.ADD(rd1, rs1, rs2);
        x.code.SRLI(rx, rs2, 1);   // floor(b/2)
        x.code.ADD(rd2, rs1, rx);  // a + floor(b/2)
        x.code.ANDI(ry, rs2, 1);   // b % 2 == 1 ?
        x.code.ADD(ry, ry, rx);    // ceil(b/2)
        x.code.ADD(rd2, rd2, ry);

        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* */
struct ADD_Split2 : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    uint32_t a, b, b_low, b_high;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.reg());
        ATTRIBUTE(rs2, r.reg());
        ATTRIBUTE(rd1, r.unique_reg({rs1, rs2, zero}));
        ATTRIBUTE(rd2, r.unique_reg({rd1, rs1, rs2, zero}));
        ATTRIBUTE(a, r.reg_val());
        ATTRIBUTE(b, r.reg_val());
        b_low = b / 2;
        b_high = b % 2 == 0 ? b_low : b_low + 1;

        x.code.LI(rs1, a);
        x.code.LI(rs2, b);
        x.code.ADD(rd1, rs1, rs2);
        x.code.ADD(rd2, rs1, zero);
        x.code.LI(rs2, b_low);
        x.code.ADD(rd2, rd2, rs2);
        x.code.LI(rs2, b_high);
        x.code.ADD(rd2, rd2, rs2);

        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* */
struct ADD_Change : public test_rule_if {
    unsigned rd, rs1, rs2;
    uint32_t a, b;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.reg());
        ATTRIBUTE(rs2, r.reg());
        ATTRIBUTE(rd, r.unique_reg({rs1, rs2, zero}));
        ATTRIBUTE(a, r.reg_val());
        ATTRIBUTE(b, r.reg_val());

        x.code.LI(rs1, a);
        x.code.LI(rs2, b);
        x.code.ADD(rd, rs1, rs2);
        x.run();

        if (b == 0 || rs2 == zero) {
            x.check(x.get_reg(rd) == x.get_reg(rs1));
        } else {
            x.check(x.get_reg(rd) != x.get_reg(rs1));
        }
    }
};
/* x << (s + 1) == x << s << 1 */
struct SLLI_Meta1 : public test_rule_if {
    unsigned rs1, rd1, rd2;
    uint32_t a, b;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.unique_reg({zero}));
        ATTRIBUTE(rd1, r.unique_reg({zero, rs1}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rs1, rd1}));
        ATTRIBUTE(a, r.reg_val());
        ATTRIBUTE(b, r.reg_val());

        // A shift further than the width of the type being shifted is undefined.
        a %= 31;
        x.code.ADDI(rs1, zero, b);
        x.code.SLLI(rd1, rs1, a + 1);
        x.code.SLLI(rd2, rs1, a);
        x.code.SLLI(rd2, rd2, 1);
        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* x << (s + 1) == x << s << 1 */
struct SLL_Meta1 : public test_rule_if {
    unsigned rs1, rs2, rd1, rd2;
    uint32_t a, b;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(a, r.i_imm());
        ATTRIBUTE(b, r.i_imm());

        // A shift further than the width of the type being shifted is undefined.
        a %= 31;
        x.code.ADDI(rs1, zero, b);
        x.code.LI(rs2, a + 1);
        x.code.SLL(rd1, rs1, rs2);
        x.code.LI(rs2, a);
        x.code.SLL(rd2, rs1, rs2);
        x.code.LI(rs2, 1);
        x.code.SLL(rd2, rd2, rs2);
        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* x << (s + 1) >= x << s */
struct SLL_Meta2 : public test_rule_if {
    unsigned rs1, rs2, rd1, rd2, rd3;
    uint32_t a, b;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rd3, &rs1, &rs2);
        ATTRIBUTE(a, (r.i_imm() & 0x1ff) % 31);
        ATTRIBUTE(b, (r.i_imm() & 0x1ffff) >> (a + 1));

        x.code.LI(rs1, b);
        x.code.LI(rs2, a);
        x.code.SLL(rd1, rs1, rs2);

        x.code.LI(rs1, b);
        x.code.LI(rs2, a + 1);
        x.code.SLL(rd2, rs1, rs2);

        x.code.SLT(rd3, rd1, rd2);
        x.run();

        x.check(x.get_reg(rd2) >= x.get_reg(rd1));
        x.check((x.get_reg(rd2) == 0) || x.get_reg(rd3));
    }
};
/* x << (s + 1) <= x << s */
struct SRL_Meta2 : public test_rule_if {
    unsigned rs1, rs2, rd1, rd2, rd3;
    uint32_t a, b;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rd3, &rs1, &rs2);
        ATTRIBUTE(a, (r.i_imm() & 0x1ff) % 31);
        ATTRIBUTE(b, r.i_imm() & 0x1ff);

        x.code.LI(rs1, b);
        x.code.LI(rs2, a);
        x.code.SRL(rd1, rs1, rs2);

        x.code.LI(rs1, b);
        x.code.LI(rs2, a + 1);
        x.code.SRL(rd2, rs1, rs2);

        x.code.SLT(rd3, rd2, rd1);
        x.run();

        x.check(x.get_reg(rd2) <= x.get_reg(rd1));
        x.check((x.get_reg(rd2) == 0) || x.get_reg(rd3));
    }
};
/* x >> (s + 1) == x >> s >> 1 */
struct SRLI_Meta1 : public test_rule_if {
    unsigned rs1, rd1, rd2;
    uint32_t a, b;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.unique_reg({zero}));
        ATTRIBUTE(rd1, r.unique_reg({zero, rs1}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rs1, rd1}));
        ATTRIBUTE(a, r.reg_val());
        ATTRIBUTE(b, r.reg_val());

        a %= 31;  // A shift further than the width of the type being shifted is undefined.
        x.code.ADDI(rs1, zero, b);
        x.code.SRLI(rd1, rs1, a + 1);
        x.code.SRLI(rd2, rs1, a);
        x.code.SRLI(rd2, rd2, 1);
        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* x >> (s + 1) == x >> s >> 1 */
struct SRL_Meta1 : public test_rule_if {
    unsigned rs1, rs2, rd1, rd2;
    uint32_t a, b;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(a, r.reg_val());
        ATTRIBUTE(b, r.reg_val());

        a %= 31;  // A shift further than the width of the type being shifted is undefined.
        x.code.ADDI(rs1, zero, b);
        x.code.LI(rs2, a + 1);
        x.code.SRL(rd1, rs1, rs2);
        x.code.LI(rs2, a);
        x.code.SRL(rd2, rs1, rs2);
        x.code.LI(rs2, 1);
        x.code.SRL(rd2, rd2, rs2);
        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* a XOR b == a XOR (b AND c)) XOR (b AND ~c) */
struct XOR_Meta1 : public test_rule_if {
    unsigned rd1, rd2, rs1;
    uint32_t a, b, c;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rd1, r.unique_reg({zero}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rd1}));
        ATTRIBUTE(rs1, r.unique_reg({zero, rd1, rd2}));
        ATTRIBUTE(a, r.reg_val());
        ATTRIBUTE(b, r.reg_val());
        ATTRIBUTE(c, r.reg_val());

        x.code.ADDI(rs1, zero, b);
        x.code.ANDI(rd1, rs1, c);
        x.code.XORI(rd1, rd1, a);
        x.code.ADDI(rs1, zero, b);
        x.code.ANDI(rd2, rs1, ~c);
        x.code.XOR(rd1, rd1, rd2);
        x.code.ADDI(rs1, zero, a);
        x.code.XORI(rd2, rs1, b);

        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* a & b = ~(~a | ~b) */
struct AND_OR_1 : public test_rule_if {
    unsigned rd1, rd2, rs1;
    uint32_t a, b;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rd1, r.unique_reg({zero}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rd1}));
        ATTRIBUTE(rs1, r.unique_reg({zero, rd1, rd2}));
        ATTRIBUTE(a, r.reg_val());
        ATTRIBUTE(b, r.reg_val());

        x.code.ADDI(rs1, zero, a);
        x.code.ANDI(rd1, rs1, b);
        x.code.ADDI(rs1, zero, ~a);
        x.code.ORI(rd2, rs1, ~b);
        x.run();
        x.check(x.get_reg(rd1) == ~x.get_reg(rd2));
    }
};
/* c + a + (-a)  == c */
struct ADD_Meta1 : public test_rule_if {
    unsigned rd;
    uint32_t c, a;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd);
        ATTRIBUTE(a, r.i_imm() & 0xfff);
        ATTRIBUTE(c, r.i_imm() & 0xfff);
        x.code.ADDI(rd, zero, c);
        x.code.ADDI(rd, rd, a);
        x.code.ADDI(rd, rd, -a);
        x.run();
        // TODO: This will zero extend zero at times. Is this correct?
        //printf("%X\n", x.get_reg(rd) & 0xfff);
        x.check((x.get_reg(rd) & 0xfff) == c);
    }
};
/* ADDI(rd, i1, i2) == ADDI(rd, zero, i1 + i2) */
struct ADD_Meta2 : public test_rule_if {
    // TODO: How should overflows be handled?
    unsigned rd1, rd2;
    uint32_t i1, i2;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2);
        ATTRIBUTE(i1, r.i_imm() & 0xff);
        ATTRIBUTE(i2, r.i_imm() & 0xff);

        x.code.LI(rd1, 0);
        x.code.ADDI(rd1, rd1, i1);
        x.code.ADDI(rd1, rd1, i2);
        x.code.ADDI(rd2, zero, i1 + i2);

        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* ADDI(rd, rs1, i) == <rs2 = i, ADD(rd, rs1, rs2)> */
struct ADD_ADDI_Equiv : public test_rule_if {
    // TODO: How should overflows be handled?
    unsigned rd1, rd2, rs1, rs2;
    uint32_t i, c;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rd1, r.unique_reg({zero}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rd1}));
        ATTRIBUTE(rs1, r.unique_reg({zero, rd1, rd2}));
        ATTRIBUTE(rs2, r.unique_reg({zero, rd1, rd2, rs1}));
        ATTRIBUTE(i, r.reg_val());
        ATTRIBUTE(c, r.reg_val());

        x.code.ADDI(rs1, zero, c);
        x.code.ADDI(rd1, rs1, i);
        x.code.ADDI(rs1, zero, c);
        x.code.ADDI(rs2, zero, i);
        x.code.ADD(rd2, rs1, rs2);

        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* <rs1 = i1, ADDI(rd, rs1, i2)> == <rs1 = i2, ADDI(rd, rs1, i1)> */
struct ADDI_Comm : public test_rule_if {
    unsigned rd1, rd2, rs1;
    uint32_t i1, i2;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());

        x.code.LI(rs1, i1);
        x.code.ADDI(rd1, rs1, i2);
        x.code.LI(rs1, i2);
        x.code.ADDI(rd2, rs1, i1);

        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* rs1 = X; rs2 = -X; ADD(rd, rs1, rs2) == 0 */
struct ADD_Inverse : public test_rule_if {
    unsigned rd, rs1, rs2;
    uint32_t i;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rd, r.unique_reg({zero}));
        ATTRIBUTE(rs1, r.unique_reg({zero, rd}));
        ATTRIBUTE(rs2, r.unique_reg({zero, rd, rs1}));
        ATTRIBUTE(i, r.i_imm());

        x.code.LI(rs1, i);
        x.code.LI(rs2, -i);
        x.code.ADD(rd, rs1, rs2);

        x.run();
        x.check(x.get_reg(rd) == 0);
    }
};
/* rs1 = i; ADDI(rd, rs1, -i) == 0 */
struct ADDI_Inverse : public test_rule_if {
    unsigned rd, rs1, rs2;
    uint32_t i;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rd, r.unique_reg({zero}));
        ATTRIBUTE(rs1, r.unique_reg({zero, rd}));
        ATTRIBUTE(i, r.i_imm());

        // TODO: For i = fffff800, sign bit is extended, i.e. rd = fffff000 (-0, "negative zero").
        x.code.LI(rs1, i);
        x.code.ADDI(rd, rs1, -i);
        x.run();
        x.check((x.get_reg(rd) & 0xfff) == 0);
    }
};
/* JAL(rd,4) == AUIPC(rd,0) */
struct JAL_AUIPC_Equiv : public test_rule_if {
    // TODO: Double check correctness of this test case after finding out
    // what's wrong with the branch test cases.
    unsigned rd1, rd2;
    uint32_t i;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rd1, r.unique_reg({zero}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rd1}));
        ATTRIBUTE(i, r.reg_val());

        auto delta1 = -x.core.pc;
        x.code.JAL(rd1, 4);
        x.run();
        delta1 += x.core.pc;

        auto delta2 = -x.core.pc;
        x.code.AUIPC(rd2, 0);
        x.run();
        delta2 += x.core.pc;

        x.check(delta1 == delta2);
    }
};
/* JAL(rd,0) leaves PC unchanged */
struct JAL_zero : public test_rule_if {
    unsigned rd1;
    uint32_t i;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rd1, r.unique_reg({zero}));
        int pc1 = x.core.pc;
        x.code.JAL(rd1, 0);
        x.run();
        int pc2 = x.core.pc;
        x.check(pc1 == pc2);
    }
};
/* JAL can jump backwards and forwards. */
struct JAL_back_forth : public test_rule_if {
    unsigned rd1, rd2;
    uint32_t i;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2);
        ATTRIBUTE(i, align_memory_addr<4>(r.i_imm() & 0xff));

        int pc1 = x.core.pc;
        x.code.JAL(rd1, i);
        x.code.JAL(rd2, -i);
        x.run();
        int pc2 = x.core.pc;

        x.check(pc1 == pc2);
        x.check(pc1 == (int)x.get_reg(rd1) - 4);
    }
};
/* <rs1 = i1, JALR(rd, rs1 & ~1, i2 & ~1)> => PC = i1 + i2 */
struct JALR_Additive : public test_rule_if {
    unsigned rd, rs1;
    int i1, i2;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd, &rs1);
        ATTRIBUTE(i1, r.i_imm() & ~1);
        ATTRIBUTE(i2, r.i_imm() & ~1);

        x.code.ADDI(rs1, zero, i1);
        x.code.JALR(rd, rs1, i2);
        x.run();
        x.check((int)x.core.pc == i1 + i2);
    }
};
/* Test for overflow of I-type immediate. */
struct JALR_Overflow : public test_rule_if {
    unsigned rd;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rd, r.unique_reg({zero}));

        // Sign extend immediate.
        int i1 = 1 << 10 << 20 >> 20;
        x.code.JALR(rd, zero, i1);
        x.run();
        x.check((int)x.core.pc == i1);

        // Sign extend immediate.
        int i2 = 1 << 11 << 20 >> 20;
        x.code.JALR(rd, zero, i2);
        x.run();
        x.check((int)x.core.pc == i2);
    }
};
/* rs1 = i; ADD(rd, rs1, zero) == ADDI(rd, rs1, 0) */
struct ADD_ADDI_zero : public test_rule_if {
    unsigned rd1, rd2, rs1;
    uint32_t i;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rd1, r.unique_reg({zero}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rd1}));
        ATTRIBUTE(rs1, r.unique_reg({zero, rd1, rs1}));
        ATTRIBUTE(i, r.reg_val());
        x.code.LI(rs1, i);
        x.code.ADD(rd1, rs1, zero);
        x.code.ADDI(rd2, rs1, 0);
        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* Arithmetic shifts preserves sign. */
struct SRAI_preserves_sign : public test_rule_if {
    unsigned rd, rs1;
    uint32_t i;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd, &rs1);
        ATTRIBUTE(i, r.i_imm() && 0xffff);

        // TODO: Zero has no sign bit. Should it? Some architectures do.
        if (i == 0) {
            return;
        }
        x.code.LI(rs1, -i);
        x.code.SRAI(rd, rs1, 1);
        x.run();
        x.check(x.get_reg(rd) & (1 << 31));
    }
};
/* Arithmetic shifts preserves sign. */
struct SRA_preserves_sign : public test_rule_if {
    unsigned rd, rs1, rs2;
    uint32_t i;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd, &rs1, &rs2);
        ATTRIBUTE(i, r.i_imm() && 0xffff);

        // TODO: Zero has no sign bit. Should it? Some architectures do.
        if (i == 0) {
            return;
        }
        x.code.LI(rs1, -i);
        x.code.LI(rs2, 1);
        x.code.SRA(rd, rs1, rs2);
        x.run();
        x.check(x.get_reg(rd) & (1 << 31));
    }
};
/* SRAI adds ones for negative values. */
struct SRAI_adds_ones : public test_rule_if {
    unsigned rd, rs1;
    int32_t shamt, i;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd, &rs1);
        ATTRIBUTE(shamt, r.s_imm() & 0b111);
        ATTRIBUTE(i, r.s_imm() & 0b111);

        x.code.LI(rs1, -i);
        x.code.SRAI(rd, rs1, shamt);
        x.run();
        //printf("%X %X %X\n", i, shamt, x.get_reg(rd));

        x.check(1);
    }
};
/* Logical left shift adds zeros. */
struct SLLI_adds_zeroes : public test_rule_if {
    unsigned rd, rs1;
    uint32_t i;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rd, r.unique_reg({zero}));
        ATTRIBUTE(rs1, r.unique_reg({zero, rd}));
        ATTRIBUTE(i, r.reg_val());

        x.code.LI(rs1, i);
        x.code.SLLI(rd, rs1, 1);

        x.run();
        x.check((x.get_reg(rd) & 1) == 0);
    }
};
/* BNE and BEQ are mutually exclusive. */
struct Branch_Exclusive1 : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    uint32_t i1, i2, i3;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());
        ATTRIBUTE(i3, r.b_imm() & 0xfff);  // Only allow positive offsets.

        if (i1 == i2) {
            return;
        }

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.code.JAL(rd1, 0);
        x.code.BNE(rs1, rs2, i3);
        x.code.JAL(rd2, 0);
        x.run();
        x.check(x.get_reg(rd2) == x.get_reg(rd1) + i3);

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.code.JAL(rd1, 0);
        x.code.BEQ(rs1, rs2, i3);
        x.code.JAL(rd2, 0);
        x.run();
        x.check(x.get_reg(rd2) == x.get_reg(rd1) + 4);
    }
};
/* BEQ/BGE(U) and BNE, BLT, BLTU are mutually exclusive. */
struct Branch_Exclusive2 : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    uint32_t i1, i2, i3;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.b_imm() & 0xfff);  // Only allow positive offsets.

        if (i2 == 4) {
            return;
        }

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i1);
        x.code.JAL(rd1, 0);
        x.code.BEQ(rs1, rs2, i2);
        x.code.JAL(rd2, 0);
        x.run();
        x.check((i1 == i2) || x.get_reg(rd2) == x.get_reg(rd1) + i2);

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i1);
        x.code.JAL(rd1, 0);
        x.code.BGE(rs1, rs2, i2);
        x.code.JAL(rd2, 0);
        x.run();
        x.check((i1 == i2) || x.get_reg(rd2) == x.get_reg(rd1) + i2);

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i1);
        x.code.JAL(rd1, 0);
        x.code.BGEU(rs1, rs2, i2);
        x.code.JAL(rd2, 0);
        x.run();
        x.check((i1 == i2) || x.get_reg(rd2) == x.get_reg(rd1) + i2);

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i1);
        x.code.JAL(rd1, 0);
        x.code.BNE(rs1, rs2, i2);
        x.code.JAL(rd2, 0);
        x.run();
        x.check((i1 == i2) || x.get_reg(rd2) != x.get_reg(rd1) + i2);

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i1);
        x.code.JAL(rd1, 0);
        x.code.BLT(rs1, rs2, i2);
        x.code.JAL(rd2, 0);
        x.run();
        x.check((i1 == i2) || x.get_reg(rd2) != x.get_reg(rd1) + i2);

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i1);
        x.code.JAL(rd1, 0);
        x.code.BLTU(rs1, rs2, i2);
        x.code.JAL(rd2, 0);
        x.run();
        x.check((i1 == i2) || x.get_reg(rd2) != x.get_reg(rd1) + i2);
    }
};
/* BLTU(rs1, rs2) || BLTU(rs2, rs1) */
struct BLTU_Meta1 : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    uint32_t i1, i2, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());
        ATTRIBUTE(off, r.b_imm() & 0xfff);  // Only allow positive offsets.

        if (i1 == i2 || off == 4) {
            return;
        }

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.code.JAL(rd1, 0);
        x.code.BLTU(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();
        bool bltu1 = x.get_reg(rd2) == (x.get_reg(rd1) + off);

        x.code.LI(rs1, i2);
        x.code.LI(rs2, i1);
        x.code.JAL(rd1, 0);
        x.code.BLTU(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();
        bool bltu2 = x.get_reg(rd2) == (x.get_reg(rd1) + off);

        x.check(bltu1 != bltu2);
    }
};
/* BLT(rs1, rs2) || BLTU(rs2, rs1) */
struct BLT_Meta1 : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    uint32_t i1, i2, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());
        ATTRIBUTE(off, r.b_imm() & 0xfff);  // Only allow positive offsets.

        if (i1 == i2 || off == 4) {
            return;
        }

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.code.JAL(rd1, 0);
        x.code.BLT(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();
        bool bltu1 = x.get_reg(rd2) == x.get_reg(rd1) + off;

        x.code.LI(rs1, i2);
        x.code.LI(rs2, i1);
        x.code.JAL(rd1, 0);
        x.code.BLT(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();
        bool bltu2 = x.get_reg(rd2) == x.get_reg(rd1) + off;

        x.check(bltu1 != bltu2);
    }
};
/* If a,b have different signs and neither is zero: 
   abs(a + b) < abs(a) + abs(b) (triangle inequality) */
struct BLT_Triangle : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t i1, i2, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());
        ATTRIBUTE(off, r.b_imm() & 0xfff);  // Only allow positive offsets.

        if ((i1 < 0) == (i2 < 0)) {
            return;
        }
        if (off == 4 || i1 == 0 || i2 == 0) {
            return;
        }

        x.code.LI(rs1, abs(i1 + i2));
        x.code.LI(rs2, abs(i1) + abs(i2));
        x.code.JAL(rd1, 0);
        x.code.BLT(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();
        //printf("BLT2: %X %X\n", i1, i2);

        x.check(x.get_reg(rd2) == x.get_reg(rd1) + off);
    }
};
/* abs(a) + abs(b) >= abs(a + b) (triangle inequality) */
struct BGE_Triangle : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t i1, i2, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());
        ATTRIBUTE(off, r.b_imm() & 0xfff);  // Only allow positive offsets.

        if (off == 4) return;

        x.code.LI(rs1, abs(i1) + abs(i2));
        x.code.LI(rs2, abs(i1 + i2));
        x.code.JAL(rd1, 0);
        x.code.BGE(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();

        x.check(x.get_reg(rd2) == x.get_reg(rd1) + off);
    }
};
/* (a <= b) == (b >= a) */
struct BGE_BLTE_Equiv : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t i1, i2, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm() & 0xfff);
        ATTRIBUTE(i2, r.i_imm() & 0xfff);
        ATTRIBUTE(off, r.b_imm() & 0xfff);  // Only allow positive offsets.

        if (off == 4) return;

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.code.JAL(rd1, 0);
        x.code.BGE(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();
        bool b1 = x.get_reg(rd2) == x.get_reg(rd1) + off;

        x.code.LI(rs1, i2);
        x.code.LI(rs2, i1);
        x.code.JAL(rd1, 0);
        x.code.BLT(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();
        bool b2 = x.get_reg(rd2) == x.get_reg(rd1) + off;

        x.code.LI(rs1, i2);
        x.code.LI(rs2, i1);
        x.code.JAL(rd1, 0);
        x.code.BEQ(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();
        bool b3 = x.get_reg(rd2) == x.get_reg(rd1) + off;

        x.check(b1 == (b2 || b3));
    }
};
/* BLT branches iff SLT == true. */
struct BLT_SLT_Equiv : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t i1, i2, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());
        ATTRIBUTE(off, r.b_imm() & 0xfff);  // Only allow positive offsets.

        if (off == 4) return;

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.code.JAL(rd1, 0);
        x.code.BLT(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();
        bool b = x.get_reg(rd2) == x.get_reg(rd1) + off;

        x.code.SLT(rd1, rs1, rs2);
        x.run();
        x.check(b == x.get_reg(rd1));
    }
};
/* BLT(rs1, rs2, off) branches iff SLT(rd, rs1, rs2) == true. */
struct BGE_SLT_Equiv : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t i1, i2, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());
        ATTRIBUTE(off, r.b_imm() & 0xfff);  // Only allow positive offsets.

        if (off == 4) return;

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.code.JAL(rd1, 0);
        x.code.BGE(rs1, rs2, off);
        x.code.JAL(rd2, 0);
        x.run();
        bool b = x.get_reg(rd2) == x.get_reg(rd1) + off;

        x.code.SLT(rd1, rs1, rs2);
        x.run();
        x.check(b == !x.get_reg(rd1));
    }
};
/* Data written with SB can be read back with load. */
struct SB_Store_Load : public test_rule_if {
    unsigned rd, rs1, rs2;
    uint32_t addr, val, off;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.unique_reg({zero}));
        ATTRIBUTE(rs2, r.unique_reg({zero, rs1}));
        ATTRIBUTE(rd, r.unique_reg({zero, rs1, rs2}));
        ATTRIBUTE(addr, r.s_imm());
        ATTRIBUTE(off, r.s_imm());
        ATTRIBUTE(val, r.reg_val() & 0xff);

        x.code.LI(rs1, addr);
        x.code.LI(rs2, val);
        x.code.SB(rs2, rs1, off);
        x.code.LB(rd, rs1, off);
        x.run();
        x.check((x.get_reg(rd) & 0xff) == x.get_reg(rs2));
    }
};
/* Data written with SH can be read back with load. */
struct SH_Store_Load : public test_rule_if {
    unsigned rd, rs1, rs2;
    uint32_t addr, val, off;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.unique_reg({zero}));
        ATTRIBUTE(rs2, r.unique_reg({zero, rs1}));
        ATTRIBUTE(rd, r.unique_reg({zero, rs1, rs2}));
        ATTRIBUTE(addr, r.s_imm());
        ATTRIBUTE(off, r.s_imm());
        ATTRIBUTE(val, r.reg_val() & 0xff);

        x.code.LI(rs1, addr);
        x.code.LI(rs2, val);
        x.code.SH(rs2, rs1, off);
        x.code.LH(rd, rs1, off);
        x.run();
        x.check((x.get_reg(rd) & 0xff) == x.get_reg(rs2));
    }
};
/* LW(rs1+off) == LHU(rs1+off) | (LHU(rs1+off+2) << 16) */
struct LW_LHU_Equiv : public test_rule_if {
    unsigned rs1, rs2, rd, rd1, rd2;
    uint32_t addr, val;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.unique_reg({zero}));
        ATTRIBUTE(rs2, r.unique_reg({zero, rs1}));
        ATTRIBUTE(rd, r.unique_reg({zero, rs1, rs2}));
        ATTRIBUTE(rd1, r.unique_reg({zero, rs1, rs2, rd}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rs1, rs2, rd1}));
        ATTRIBUTE(addr, align_memory_addr<4>(r.s_imm()));
        ATTRIBUTE(val, r.s_imm());

        x.code.LI(rs2, val);
        x.code.LI(rs1, addr);
        x.code.SW(rs2, rs1, 0);

        x.code.LI(rs1, addr);
        x.code.LW(rd1, rs1, 0);
        x.code.LI(rs1, addr + 2);
        x.code.LH(rd2, rs1, 0);
        x.run();
        x.check(val == (x.get_reg(rd1) | (x.get_reg(rd2) << 16)));
    }
};
/* LHU(rs1+off) == LBU(rs1+off) | (LBU(rs1+off+1) << 8) */
struct LH_LB_Equiv : public test_rule_if {
    unsigned rs1, rs2, rd, rd1, rd2;
    uint32_t addr, val;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.unique_reg({zero}));
        ATTRIBUTE(rs2, r.unique_reg({zero, rs1}));
        ATTRIBUTE(rd, r.unique_reg({zero, rs1, rs2}));
        ATTRIBUTE(rd1, r.unique_reg({zero, rs1, rs2, rd}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rs1, rs2, rd1}));
        ATTRIBUTE(addr, align_memory_addr<2>(r.s_imm()));
        ATTRIBUTE(val, r.s_imm());

        x.code.LI(rs2, val);
        x.code.LI(rs1, addr);
        x.code.SH(rs2, rs1, 0);

        x.code.LI(rs1, addr);
        x.code.LB(rd1, rs1, 0);
        x.code.LI(rs1, addr + 1);
        x.code.LB(rd2, rs1, 0);
        x.run();

        x.check((val & 0xffff) == (((x.get_reg(rd2) & 0xff) << 8) | (x.get_reg(rd1) & 0xff)));
    }
};
/* Two LBU are equivalent to one LHU */
struct LHU_LBU_Equiv : public test_rule_if {
    unsigned rs1, rs2, rd, rd1, rd2;
    uint32_t addr, val;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.unique_reg({zero}));
        ATTRIBUTE(rs2, r.unique_reg({zero, rs1}));
        ATTRIBUTE(rd, r.unique_reg({zero, rs1, rs2}));
        ATTRIBUTE(rd1, r.unique_reg({zero, rs1, rs2, rd}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rs1, rs2, rd1}));
        ATTRIBUTE(addr, align_memory_addr<2>(r.s_imm()));
        ATTRIBUTE(val, r.s_imm());

        x.code.LI(rs2, val);
        x.code.LI(rs1, addr);
        x.code.SH(rs2, rs1, 0);

        x.code.LI(rs1, addr);
        x.code.LBU(rd1, rs1, 0);
        x.code.LI(rs1, addr + 1);
        x.code.LBU(rd2, rs1, 0);
        x.run();

        x.check((val & 0xffff) == ((x.get_reg(rd2) << 8) | x.get_reg(rd1)));
    }
};
/* Compare signed/unsigned load with same width. */
struct LH_LHU_Equiv : public test_rule_if {
    unsigned rs1, rs2, rd, rd1, rd2;
    uint32_t addr, val;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(rs1, r.unique_reg({zero}));
        ATTRIBUTE(rs2, r.unique_reg({zero, rs1}));
        ATTRIBUTE(rd, r.unique_reg({zero, rs1, rs2}));
        ATTRIBUTE(rd1, r.unique_reg({zero, rs1, rs2, rd}));
        ATTRIBUTE(rd2, r.unique_reg({zero, rs1, rs2, rd1}));
        ATTRIBUTE(addr, align_memory_addr<2>(r.s_imm()));
        ATTRIBUTE(val, r.s_imm());

        x.code.LI(rs2, val);
        x.code.LI(rs1, addr);
        x.code.SH(rs2, rs1, 0);

        x.code.LI(rs1, addr);
        x.code.LH(rd1, rs1, 0);
        x.code.LHU(rd2, rs1, 0);
        x.run();

        x.check(val == x.get_reg(rd1));
        x.check((val & 0xffff) == x.get_reg(rd2));
    }
};
/* XORI(rd, rs1, -1) == ~rs1 */
struct XORI_Invert : public test_rule_if {
    unsigned rd, rs1;
    uint32_t c;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd, &rs1);
        ATTRIBUTE(c, r.i_imm());

        x.code.LI(rs1, c);
        x.code.XORI(rd, rs1, -1);
        x.run();
        x.check(~c == x.get_reg(rd));
    }
};
/* XORI(rd, rs1, I) == <rs2 = I, XOR(rd, rs1, rs2)> */
struct XOR_XORI_Equiv : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    uint32_t c1, c2;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(c1, r.i_imm());
        ATTRIBUTE(c2, r.i_imm());

        x.code.LI(rs1, c1);
        x.code.LI(rs2, c2);
        x.code.XORI(rd1, rs1, c2);
        x.code.XOR(rd2, rs1, rs2);
        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* Load upper immediate (LUI) sets the upper 20 bits of the destination 
   register to the ones specified and fills the remaining ones with zeros. */
struct LUI1 : public test_rule_if {
    unsigned rd;
    uint32_t i;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd);
        ATTRIBUTE(i, r.u_imm());
        x.code.LUI(rd, i);
        x.run();
        x.check(i == x.get_reg(rd) >> 12);
    }
};
/* AUIPC(rd, i1 + i2) == AUIPC(rd, i1), AUIPC(rd, i2) */
// TODO: I had misread the spec. This property doesn't actually hold. Think of a different test.
struct AUIPC_Additive : public test_rule_if {
    unsigned rd;
    uint32_t i;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd);
        ATTRIBUTE(i, align_memory_addr<4>(r.u_imm() & 0xff));
        x.code.AUIPC(rd, i);
        x.run();
        int o = x.get_reg(rd) >> 12;

        // TODO: Revisit spec what should be going on here. This check documents current behavior.
        x.check((o == (int)(i + 2)) || (o == (int)(i + 1)) || (o == (int)(i - 1)));
    }
};
/* ADD(rs1, -rs2) == 0 implies BEQ. */
struct ADD_BEQ_Zero : public test_rule_if {
    unsigned rd, rs1, rs2;
    int32_t i1, i2, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());
        ATTRIBUTE(off, r.b_imm() & 0xfff);

        x.code.LI(rs1, i1);
        x.code.LI(rs2, -i2);
        x.code.ADD(rd, rs1, rs2);
        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.run();

        int pc1 = x.core.pc;
        x.code.BEQ(rs1, rs2, off);
        x.run();
        int pc2 = x.core.pc;

        if (x.get_reg(rd) == 0) {
            x.check(abs(pc1 - pc2) == off);
        } else {
            x.check(abs(pc1 - pc2) == 4);
        }
    }
};
/* JAL(rd, i1 + i2) == JAL(rd, i1), JAL(rd, i2) */
struct JAL_Additive : public test_rule_if {
    void run(Executor &x, Random &r) {
        throw TraceableException("not implemented");
    }
};
/* JALR(rd, rs1, I) == JALR(rd, I, rs1) */
struct JALR_Commutative : public test_rule_if {
    unsigned rd1, rd2, rs1;
    int32_t i1, i2;
    void run(Executor &x, Random &r) {
        ATTRIBUTE(i1, r.i_imm() & 0xfff);
        ATTRIBUTE(i2, r.i_imm() & 0xfff);
        REGISTERS(r, &rd1, &rd2, &rs1);

        x.code.LI(rs1, i1);
        x.run();
        int pc0 = x.core.pc & 0xfff;

        x.code.JALR(rd1, rs1, i2);
        x.run();
        int pc1 = x.core.pc & 0xfff;

        x.code.LI(rs1, i2);
        x.run();
        int pc2 = x.core.pc & 0xfff;

        x.code.JALR(rd2, rs1, i1);
        x.run();
        int pc3 = x.core.pc & 0xfff;

        x.check(pc1 == pc3);
        x.check((x.get_reg(rd1) & 0xfff) - pc0);
        x.check((x.get_reg(rd2) & 0xfff) - pc2);
    }
};
/* SLTI(rd, rs1, I) => !SLTI(rd, I, rs1) */
struct SLTI_1 : public test_rule_if {
    unsigned rd1, rd2, rs1;
    int32_t i1, i2;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());

        x.code.LI(rs1, i1);
        x.code.SLTI(rd1, rs1, i2);
        x.code.LI(rs1, i2);
        x.code.SLTI(rd2, rs1, i1);
        x.run();

        if (i1 == i2) {
            x.check(x.get_reg(rd1) == x.get_reg(rd2));
        } else {
            x.check(x.get_reg(rd1) != x.get_reg(rd2));
        }
    }
};
/* SLTIU(rd, rs1, I) => !SLTIU(rd, I, rs1) */
struct SLTIU_1 : public test_rule_if {
    unsigned rd1, rd2, rs1;
    int32_t i1, i2;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());

        x.code.LI(rs1, i1);
        x.code.SLTIU(rd1, rs1, i2);
        x.code.LI(rs1, i2);
        x.code.SLTIU(rd2, rs1, i1);
        x.run();

        if (i1 == i2) {
            x.check(x.get_reg(rd1) == x.get_reg(rd2));
        } else {
            x.check(x.get_reg(rd1) != x.get_reg(rd2));
        }
    }
};
/* SLTI: (a < b) == !(-a < -b) */
struct SLTI_2 : public test_rule_if {
    unsigned rd1, rd2, rs1;
    int32_t i1, i2;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1);
        ATTRIBUTE(i1, r.i_imm() & 0x7ff);
        ATTRIBUTE(i2, r.i_imm() & 0x7ff);

        x.code.LI(rs1, i1);
        x.code.SLTI(rd1, rs1, i2);
        x.code.LI(rs1, -i1);
        x.code.SLTI(rd2, rs1, -i2);
        x.run();

        if (i1 == i2) {
            x.check(x.get_reg(rd1) == x.get_reg(rd2));
        } else {
            x.check(x.get_reg(rd1) == !x.get_reg(rd2));
        }
    }
};
/* SUB(a, b) == ADD(a, -b) */
struct SUB_ADD_Equiv : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t i1, i2;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());
        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.code.SUB(rd1, rs1, rs2);
        x.code.LI(rs2, -i2);
        x.code.ADD(rd2, rs1, rs2);
        x.run();
        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* SRLI and SLLI are inverses of each other */
struct SRLI_SLLI_Inverse : public test_rule_if {
    unsigned rd, rs1;
    int32_t i1, shamt;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd);
        ATTRIBUTE(i1, r.i_imm() & 0xff);
        ATTRIBUTE(shamt, (r.i_imm() & 0xffff) % (32 - 8));

        x.code.LI(rd, i1);
        x.code.SLLI(rd, rd, shamt);
        x.code.SRLI(rd, rd, shamt);
        x.run();

        x.check((int)x.get_reg(rd) == i1);
    }
};
/* rs1 = -1; SRLI(rd, rs1, I) => (rd & (1<<31) == 0) (sign bit disappears) */
struct SRLI_sign : public test_rule_if {
    unsigned rd, rs1;
    int32_t i, shamt;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd);
        ATTRIBUTE(i, r.i_imm());
        ATTRIBUTE(shamt, r.i_imm() & 0b11111);

        x.code.MV(rd, i);
        x.code.SRLI(rd, rd, shamt);
        x.run();

        x.check(((int)x.get_reg(rd) & (1 << 31)) == 0);
    }
};
/* a & b = ~(~a | ~b) */
struct AND_OR_Equiv : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t a, b;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(a, r.i_imm());
        ATTRIBUTE(b, r.i_imm());
        x.code.LI(rs1, a);
        x.code.LI(rs2, b);
        x.code.AND(rd1, rs1, rs2);
        x.code.LI(rs1, ~a);
        x.code.LI(rs2, ~b);
        x.code.OR(rd2, rs1, rs2);
        x.run();
        x.check(x.get_reg(rd1) == ~x.get_reg(rd2));
    }
};
/* SLTI: (a < b) => (a + c < b + c) */
struct SLTI_3 : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t i1, i2, c;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm() & 0xff);
        ATTRIBUTE(i2, r.i_imm() & 0xff);
        ATTRIBUTE(c, r.i_imm() & 0xff);

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.code.SLT(rd1, rs1, rs2);
        x.code.LI(rs1, i1 + c);
        x.code.LI(rs2, i2 + c);
        x.code.SLT(rd2, rs1, rs2);
        x.run();

        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* SLTI: SLTU(rd, rs2, -rs2) == 1*/
struct SLTI_4 : public test_rule_if {
    unsigned rd, rs1, rs2;
    int32_t i;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd, &rs1, &rs2);
        ATTRIBUTE(i, r.i_imm() & 0xffff);

        x.code.LI(rs1, i);
        x.code.LI(rs2, -i);
        x.code.SLTU(rd, rs1, rs2);
        x.run();

        if (i == 0) {
            x.check(x.get_reg(rd) == 0);
        } else {
            x.check(x.get_reg(rd) == 1);
        }
    }
};
/* (a | (b & c)) | (b & ~c) == a | b */
struct OR_Equiv : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t a, b, c;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(a, r.i_imm());
        ATTRIBUTE(b, r.i_imm());
        ATTRIBUTE(c, r.i_imm());

        x.code.LI(rs1, b);
        x.code.ANDI(rd1, rs1, c);
        x.code.ORI(rd1, rd1, a);
        x.code.LI(rs1, b);
        x.code.ANDI(rd2, rs1, ~c);
        x.code.LI(rs1, a);
        x.code.ORI(rd1, rs1, b);
        x.code.LI(rs1, a);
        x.code.ORI(rd2, rs1, b);
        x.run();

        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* (a & (b | c)) & (b | ~c) == a & b */
struct AND_Equiv : public test_rule_if {
    unsigned rd1, rd2, rs1, rs2;
    int32_t a, b, c;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rd1, &rd2, &rs1, &rs2);
        ATTRIBUTE(a, r.i_imm());
        ATTRIBUTE(b, r.i_imm());
        ATTRIBUTE(c, r.i_imm());

        x.code.LI(rs1, b);
        x.code.ORI(rd1, rs1, c);
        x.code.ANDI(rd1, rd1, a);
        x.code.LI(rs1, b);
        x.code.ORI(rd2, rs1, ~c);
        x.code.LI(rs1, a);
        x.code.ANDI(rd1, rs1, b);
        x.code.LI(rs1, a);
        x.code.ANDI(rd2, rs1, b);
        x.run();

        x.check(x.get_reg(rd1) == x.get_reg(rd2));
    }
};
/* BEQ(rs1, rs2, 4) == PC (branch by 4 is a no-op)*/
struct BEQ_Zero : public test_rule_if {
    unsigned rs1, rs2;
    int32_t i1, i2;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rs1, &rs2);
        ATTRIBUTE(i1, r.i_imm());
        ATTRIBUTE(i2, r.i_imm());

        x.code.LI(rs1, i1);
        x.code.LI(rs2, i2);
        x.run();
        int pc1 = x.core.pc;
        x.code.BEQ(rs1, rs2, 4);
        x.run();
        int pc2 = x.core.pc;

        x.check(pc1 + 4 == pc2);
    }
};
/* BEQ(rs1, rs1, I) always taken */
struct BEQ_Dup : public test_rule_if {
    unsigned rs1, rs2;
    int32_t i, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rs1);
        ATTRIBUTE(i, r.i_imm());
        ATTRIBUTE(off, align_memory_addr<4>(r.s_imm() & 0xff));

        x.code.LI(rs1, i);
        x.run();
        int pc1 = x.core.pc;
        x.code.BEQ(rs1, rs1, off);
        x.run();
        int pc2 = x.core.pc;

        x.check(pc1 + off == pc2);
    }
};
/* BNE(rs1, rs1, I) never taken */
struct BNE_Dup : public test_rule_if {
    unsigned rs1, rs2;
    int32_t i, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rs1);
        ATTRIBUTE(i, r.i_imm());
        ATTRIBUTE(off, align_memory_addr<4>(r.s_imm() & 0xff));

        x.code.LI(rs1, i);
        x.run();
        int pc1 = x.core.pc;
        x.code.BNE(rs1, rs1, off);
        x.run();
        int pc2 = x.core.pc;

        x.check(pc1 + 4 == pc2);
    }
};
/* BLT(rs1, rs1, I) never taken */
struct BLT_Dup : public test_rule_if {
    unsigned rs1, rs2;
    int32_t i, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rs1);
        ATTRIBUTE(i, r.i_imm());
        ATTRIBUTE(off, align_memory_addr<4>(r.s_imm() & 0xff));

        x.code.LI(rs1, i);
        x.run();
        int pc1 = x.core.pc;
        x.code.BLT(rs1, rs1, off);
        x.run();
        int pc2 = x.core.pc;

        x.check(pc1 + 4 == pc2);
    }
};
/* BGE(rs1, rs1, I) always taken */
struct BGE_Dup : public test_rule_if {
    unsigned rs1, rs2;
    int32_t i, off;
    void run(Executor &x, Random &r) {
        REGISTERS(r, &rs1);
        ATTRIBUTE(i, r.i_imm());
        ATTRIBUTE(off, align_memory_addr<4>(r.s_imm() & 0xff));

        x.code.LI(rs1, i);
        x.run();
        int pc1 = x.core.pc;
        x.code.BGE(rs1, rs1, off);
        x.run();
        int pc2 = x.core.pc;

        x.check(pc1 + off == pc2);
    }
};

/* Common */
std::vector<std::shared_ptr<test_rule_if>> rules_ = {
    std::make_shared<SRL_Meta2>(),
    std::make_shared<SLL_Meta2>(),
};
std::vector<std::shared_ptr<test_rule_if>> rules = {
    std::make_shared<ADD_ADDI_Equiv>(),
    std::make_shared<ADD_ADDI_zero>(),
    std::make_shared<ADD_Assoc>(),
    std::make_shared<ADD_BEQ_Zero>(),
    std::make_shared<ADD_Change>(),
    std::make_shared<ADD_Comm>(),
    std::make_shared<ADD_Inverse>(),
    std::make_shared<ADDI_Assoc>(),
    std::make_shared<ADDI_Inverse>(),
    std::make_shared<ADDI_Comm>(),
    std::make_shared<ADD_Meta1>(),
    std::make_shared<ADD_Meta2>(),
    std::make_shared<AND_OR_1>(),
    std::make_shared<AND_OR_Equiv>(),
    std::make_shared<ADD_Split1>(),
    std::make_shared<ADD_Split2>(),
    //std::make_shared<AUIPC_Additive>(),
    std::make_shared<BEQ_Dup>(),
    std::make_shared<BEQ_Zero>(),
    std::make_shared<BGE_Dup>(),
    std::make_shared<BGE_Triangle>(),
    std::make_shared<BGE_BLTE_Equiv>(),
    std::make_shared<BGE_SLT_Equiv>(),
    std::make_shared<BLT_Dup>(),
    std::make_shared<BLT_Meta1>(),
    std::make_shared<BLT_SLT_Equiv>(),
    std::make_shared<BLT_Triangle>(),
    std::make_shared<BNE_Dup>(),
    std::make_shared<BLTU_Meta1>(),
    std::make_shared<Branch_Exclusive1>(),
    std::make_shared<Branch_Exclusive2>(),
    std::make_shared<JAL_back_forth>(),
    std::make_shared<JAL_AUIPC_Equiv>(),
    std::make_shared<JAL_zero>(),
    std::make_shared<JALR_Additive>(),
    std::make_shared<JALR_Commutative>(),
    std::make_shared<JALR_Overflow>(),
    std::make_shared<LH_LB_Equiv>(),
    std::make_shared<LH_LHU_Equiv>(),
    std::make_shared<LHU_Combine2>(),
    std::make_shared<LHU_LBU_Equiv>(),
    std::make_shared<LUI1>(),
    std::make_shared<LXU_LX_Rel<1>>(),
    std::make_shared<LXU_LX_Rel<2>>(),
    std::make_shared<LW_Combine2>(),
    std::make_shared<LW_LHU_Equiv>(),
    std::make_shared<LX_AddrId<LoadInstr::LB>>(),
    std::make_shared<LX_AddrId<LoadInstr::LBU>>(),
    std::make_shared<LX_AddrId<LoadInstr::LH>>(),
    std::make_shared<LX_AddrId<LoadInstr::LHU>>(),
    std::make_shared<LX_AddrId<LoadInstr::LW>>(),
    std::make_shared<LX_ExtCheck<LoadInstr::LB>>(),
    std::make_shared<LX_ExtCheck<LoadInstr::LBU>>(),
    std::make_shared<LX_ExtCheck<LoadInstr::LH>>(),
    std::make_shared<LX_ExtCheck<LoadInstr::LHU>>(),
    std::make_shared<OR_Equiv>(),
    std::make_shared<AND_Equiv>(),
    std::make_shared<SB_Store_Load>(),
    // TODO: Currently requires an atomic_unlock() which is not implemented (default interface
    // inherits from EmptyMemoryInterface, where the exception comes from).
    //std::make_shared<SH_Store_Load>(),
    std::make_shared<SRA_preserves_sign>(),
    std::make_shared<SRAI_preserves_sign>(),
    std::make_shared<SLL_Meta1>(),
    std::make_shared<SLL_Meta2>(),
    std::make_shared<SLLI_Meta1>(),
    std::make_shared<SLLI_adds_zeroes>(),
    std::make_shared<SLTI_1>(),
    std::make_shared<SLTI_2>(),
    std::make_shared<SLTI_3>(),
    std::make_shared<SLTI_4>(),
    std::make_shared<SLTIU_1>(),
    std::make_shared<SRL_Meta1>(),
    std::make_shared<SRL_Meta2>(),
    std::make_shared<SRLI_Meta1>(),
    std::make_shared<SUB_ADD_Equiv>(),
    //std::make_shared<SW_RefCheck>(), // TODO: Unimplemented memory interfaces.
    std::make_shared<SX_LX_Id<1>>(),
    std::make_shared<SX_LX_Id<2>>(),
    std::make_shared<SX_LX_Id<4>>(),
    std::make_shared<XORI_Invert>(),
    std::make_shared<XOR_Meta1>(),
    std::make_shared<XOR_XORI_Equiv>(),
};
std::shared_ptr<test_rule_if> random_rule(Random &r) {
    return rules[r(rules.size())];
}
std::string test_rule_if::to_string() {
    std::ostringstream ss;
    std::string class_name = abi::__cxa_demangle(typeid(*this).name(), 0, 0, 0);
    ss << class_name << std::endl;
    for (auto attr : attributes) {
        std::string name = boost::get<0>(attr);
        boost::any value = boost::get<1>(attr);
        ss << "\t" << name << "\t= ";
        if (typeid(unsigned) == value.type()) {
            ss << boost::any_cast<unsigned>(value);
        } else {
            ss << boost::any_cast<int>(value);
        }
        ss << std::endl;
    }
    return ss.str();
}
template <LoadInstr T>
std::string test_rule_if::to_string() {
    std::ostringstream ss;
    ss << GetEnumName<T>() << ":" << test_rule_if::to_string();
    return ss.str();
}
template <LoadInstr T>
std::string GetEnumName() {
    switch (T) {
        case LoadInstr::LB:
            return "LB";
        case LoadInstr::LBU:
            return "LBU";
        case LoadInstr::LH:
            return "LH";
        case LoadInstr::LHU:
            return "LHU";
        case LoadInstr::LW:
            return "LW";
    }
}
template <LoadInstr T>
constexpr unsigned GetAlignWidth() {
    if (T == LoadInstr::LB || T == LoadInstr::LBU) return 1;
    if (T == LoadInstr::LH || T == LoadInstr::LHU) return 2;
    return 4;
}
template <unsigned N>
int align_memory_addr(int reg, int off) {
    while (((reg + off) % N) != 0) off = (off + 1) % 2048;
    return off;
}
template <unsigned N>
int align_memory_addr(int addr) {
    if (addr % N == 0) return addr;
    return addr + (N - (addr % N));
}
