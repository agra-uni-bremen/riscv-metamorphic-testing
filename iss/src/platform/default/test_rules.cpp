#include "test_rules.h"

#include <iomanip>
#include <string>

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

/* ADD_Assoc */
std::string ADD_Assoc::to_string() {
    std::ostringstream ss;
    ss << "ADD_Assoc(\n"
       << "    rd1 = " << rd1 << "\n"
       << "    rd2 = " << rd2 << "\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rs2 = " << rs2 << "\n"
       << "    rs3 = " << rs3 << "\n"
       << ")";
    return ss.str();
}
void ADD_Assoc::randomize(Random &random) {
    rs1 = random.reg();
    rs2 = random.reg();
    rs3 = random.reg();
    rd1 = random.unique_reg({rs1, rs2, rs3, zero});
    rd2 = random.unique_reg({rd1, rs1, rs2, rs3, zero});
    a = random.reg_val();
    b = random.reg_val();
    c = random.reg_val();
}
void ADD_Assoc::run(Executor &x) {
    x.code.LI(rs1, a);
    x.code.LI(rs2, b);
    x.code.LI(rs3, c);
    x.code.ADD(rd1, rs1, rs2);
    x.code.ADD(rd1, rd1, rs3);
    x.code.ADD(rd2, rs2, rs3);
    x.code.ADD(rd2, rs1, rd2);
    x.run();
    x.check(x.get_reg(rd1) == x.get_reg(rd2));
}

/* LX_AddrId */
template <LoadInstr T>
std::string LX_AddrId<T>::to_string() {
    std::ostringstream ss;
    ss << "LX_AddrId<" << GetEnumName<T>() << ">(\n"
       << "    rd1 = " << rd1 << "\n"
       << "    rd2 = " << rd2 << "\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rs2 = " << rs2 << "\n"
       << "    a = " << a << "\n"
       << "    b = " << b << "\n"
       << "    off1 = " << off1 << "\n"
       << "    off2 = " << off2 << "\n"
       << ")";
    return ss.str();
}
template <LoadInstr T>
void LX_AddrId<T>::randomize(Random &random) {
    rs1 = random.reg();
    rs2 = random.unique_reg({rs1, zero});
    rd1 = random.unique_reg({rs1, rs2, zero});
    rd2 = random.unique_reg({rd1, rs1, rs2, zero});
    a = random.reg_val(rs1);
    off1 = align_memory_addr<GetAlignWidth<T>()>(a, random.i_imm());
    off2 = random.i_imm();
}
template <LoadInstr T>
void LX_AddrId<T>::_LX(Executor &x, unsigned rd, unsigned rs, int off) {
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
    else
        throw std::runtime_error("not implemented");
}
template <LoadInstr T>
void LX_AddrId<T>::run(Executor &x) {
    x.code.LI(rs1, a);
    _LX(x, rd1, rs1, off1);

    x.code.ADDI(rs2, rs1, off1);
    x.code.ADDI(rd2, zero, off2);
    x.code.SUB(rs2, rs2, rd2);
    _LX(x, rd2, rs2, off2);

    x.run();
    x.check(x.get_reg(rd1) == x.get_reg(rd2));
}

/* SX_LX_Id */
template <unsigned N>
std::string SX_LX_Id<N>::to_string() {
    std::ostringstream ss;
    ss << "SX_LX_Id<" << N << ">(\n"
       << "    rd = " << rd << "\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rs2 = " << rs2 << "\n"
       << "    a = " << a << "\n"
       << "    b = " << b << "\n"
       << "    off = " << off << "\n"
       << ")";
    return ss.str();
}
template <unsigned N>
void SX_LX_Id<N>::randomize(Random &random) {
    rs1 = random.reg();
    rs2 = random.reg();
    rd = random.unique_reg({zero});
    a = random.reg_val(rs1);
    b = random.reg_val();
    off = align_memory_addr<N>(a, random.i_imm());
}
template <unsigned N>
void SX_LX_Id<N>::run(Executor &x) {
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

/* LW_Combine2 */
std::string LW_Combine2::to_string() {
    std::ostringstream ss;
    ss << "LW_Combine2(\n"
       << "    rd = " << rd << "\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rx = " << rx << "\n"
       << "    ry = " << ry << "\n"
       << "    a = " << a << "\n"
       << "    off = " << off << "\n"
       << ")";
    return ss.str();
}
void LW_Combine2::randomize(Random &random) {
    rs1 = random.unique_reg({zero});
    rd = random.unique_reg({rs1, zero});
    rx = random.unique_reg({rs1, rd, zero});
    ry = random.unique_reg({rs1, rd, rx, zero});
    a = random.reg_val(rs1);
    off = align_memory_addr<4>(a, random.i_imm());
}
void LW_Combine2::run(Executor &x) {
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

/* LHU_Combine2 */
std::string LHU_Combine2::to_string() {
    std::ostringstream ss;
    ss << "LHU_Combine2(\n"
       << "    rd = " << rd << "\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rx = " << rx << "\n"
       << "    ry = " << ry << "\n"
       << "    a = " << a << "\n"
       << "    off = " << off << "\n"
       << ")";
    return ss.str();
}
void LHU_Combine2::randomize(Random &random) {
    rs1 = random.unique_reg({zero});
    rd = random.unique_reg({rs1, zero});
    rx = random.unique_reg({rs1, rd, zero});
    ry = random.unique_reg({rs1, rd, rx, zero});
    a = random.reg_val(rs1);
    off = align_memory_addr<2>(a, random.i_imm());
}
void LHU_Combine2::run(Executor &x) {
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

/* LX_ExtCheck */
template <LoadInstr T>
std::string LX_ExtCheck<T>::to_string() {
    std::ostringstream ss;
    ss << "LX_ExtCheck<" << GetEnumName<T>() << ">(\n"
       << "    rd = " << rd << "\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rx = " << rx << "\n"
       << "    a = " << a << "\n"
       << "    off = " << off << "\n"
       << ")";
    return ss.str();
}
template <LoadInstr T>
void LX_ExtCheck<T>::randomize(Random &random) {
    rs1 = random.reg();
    rd = random.reg();
    rx = random.unique_reg({rd, zero});
    a = random.reg_val(rs1);
    off = align_memory_addr<GetAlignWidth<T>()>(a, random.i_imm());
}
template <LoadInstr T>
void LX_ExtCheck<T>::run(Executor &x) {
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
        throw std::runtime_error("not supported");
    x.code.MV(rx, rd);
    x.code.SLLI(rx, rx, shamt);
    if (T == LoadInstr::LB || T == LoadInstr::LH)
        x.code.SRAI(rx, rx, shamt);
    else
        x.code.SRLI(rx, rx, shamt);
    x.run();
    x.check(x.get_reg(rd) == x.get_reg(rx));
}

/* LXU_LX_Rel */
template <unsigned N>
std::string LXU_LX_Rel<N>::to_string() {
    std::ostringstream ss;
    ss << "LXU_LX_Rel<" << N << ">(\n"
       << "    rd = " << rd << "\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rx = " << rx << "\n"
       << "    ry = " << ry << "\n"
       << "    a = " << a << "\n"
       << "    off = " << off << "\n"
       << ")";
    return ss.str();
}
template <unsigned N>
void LXU_LX_Rel<N>::randomize(Random &random) {
    rs1 = random.reg();
    rd = random.unique_reg({rs1, zero});
    rx = random.unique_reg({rs1, rd, zero});
    ry = random.unique_reg({rs1, rd, rx, zero});
    a = random.reg_val(rs1);
    off = align_memory_addr<N>(a, random.i_imm());
}
template <unsigned N>
void LXU_LX_Rel<N>::run(Executor &x) {
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
    //		std::cout << "R[rd=" << rd << "]=" << x.get_reg(rd) <<
    // std::endl; 		std::cout << "R[rx=" << rx << "]=" <<
    // x.get_reg(rx) << std::endl; 		std::cout << "R[ry=" << ry <<
    // "]=" << x.get_reg(ry) << std::endl; 		std::cout << "R[rs1=" <<
    // rs1 << "]=" << x.get_reg(rs1) << std::endl;

    x.check(x.get_reg(rd) <= x.get_reg(rx));
    x.check(x.get_reg(rd) == x.get_reg(ry));
}

/* SW_RefCheck */
std::string SW_RefCheck::to_string() {
    std::ostringstream ss;
    ss << "SW_RefCheck(\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rs2 = " << rs2 << "\n"
       << "    a = " << a << "\n"
       << "    b = " << b << "\n"
       << ")";
    return ss.str();
}
void SW_RefCheck::randomize(Random &random) {
    rs1 = random.reg();
    rs2 = random.reg();
    a = align_memory_addr<4>(random.reg_val(rs1));
    if (rs1 == rs2)
        b = a;
    else
        b = random.reg_val(rs2);
}
void SW_RefCheck::store_word(uint64_t addr, uint32_t value) {
    observed_addr = addr;
    observed_value = value;
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
void SW_RefCheck::run(Executor &x) {
    SwitchDataMemoryInterface tmp_option(x, this);
    x.code.LI(rs2, b);
    x.code.LI(rs1, a);  // load rs1 after rs2 to ensure proper alignment (in
                        // case rs1==rs2)
    x.code.SW(rs2, rs1, 0);
    x.run();
    x.check(observed_addr == a);
    x.check(observed_value == b);
}

/* ADD_Comm */
std::string ADD_Comm::to_string() {
    std::ostringstream ss;
    ss << "ADD_Comm(\n"
       << "    rd1=" << rd1 << "\n"
       << "    rd2=" << rd2 << "\n"
       << "    rs1=" << rs1 << "\n"
       << "    rs2=" << rs2 << "\n"
       << "    a=" << a << "\n"
       << "    b=" << b << "\n"
       << ")";
    return ss.str();
}
void ADD_Comm::randomize(Random &random) {
    rs1 = random.reg();
    rs2 = random.reg();
    rd1 = random.unique_reg({rs1, rs2, zero});
    rd2 = random.unique_reg({rd1, rs1, rs2, zero});
    a = random.reg_val();
    b = random.reg_val();
}
void ADD_Comm::run(Executor &x) {
    x.code.LI(rs1, a);
    x.code.LI(rs2, b);
    x.code.ADD(rd1, rs1, rs2);
    x.code.ADD(rd2, rs2, rs1);
    x.run();
    x.check(x.get_reg(rd1) == x.get_reg(rd2));
}

/* ADD_Split */
std::string ADD_Split::to_string() {
    std::ostringstream ss;
    ss << "ADD_Split(\n"
       << "    rd1 = " << rd1 << "\n"
       << "    rd2 = " << rd2 << "\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rs2 = " << rs2 << "\n"
       << "    rx = " << rx << "\n"
       << "    ry = " << ry << "\n"
       << "    a = " << a << "\n"
       << "    b = " << b << "\n"
       << ")";
    return ss.str();
}
void ADD_Split::randomize(Random &random) {
    rs1 = random.reg();
    rs2 = random.reg();
    rd1 = random.unique_reg({rs1, rs2, zero});
    rd2 = random.unique_reg({rd1, rs1, rs2, zero});
    rx = random.unique_reg({rd1, rd2, rs1, rs2, zero});
    ry = random.unique_reg({rx, rd1, rd2, rs1, rs2, zero});
    a = random.reg_val();
    b = random.reg_val();
}
void ADD_Split::run(Executor &x) {
    x.code.LI(rs1, a);
    x.code.LI(rs2, b);
    x.code.ADD(rd1, rs1, rs2);

    x.code.SRLI(rx, rs2, 1);   // floor(b/2)
    x.code.ADD(rd2, rs1, rx);  // a + floor(b/2)

    x.code.ANDI(ry, rs2, 1);  // b % 2 == 1 ?
    x.code.ADD(ry, ry, rx);   // ceil(b/2)
    x.code.ADD(rd2, rd2, ry);

    x.run();
    x.check(x.get_reg(rd1) == x.get_reg(rd2));
}

/* ADD_Split2 */
std::string ADD_Split2::to_string() {
    std::ostringstream ss;
    ss << "ADD_Split2(\n"
       << "    rd1 = " << rd1 << "\n"
       << "    rd2 = " << rd2 << "\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rs2 = " << rs2 << "\n"
       << "    a = " << a << "\n"
       << "    b = " << b << "\n"
       << "    b_low = " << b_low << "\n"
       << "    b_high = " << b_high << "\n"
       << ")";
    return ss.str();
}
void ADD_Split2::randomize(Random &random) {
    rs1 = random.reg();
    rs2 = random.reg();
    rd1 = random.unique_reg({rs1, rs2, zero});
    rd2 = random.unique_reg({rd1, rs1, rs2, zero});
    a = random.reg_val();
    b = random.reg_val();
    b_low = b / 2;
    b_high = b % 2 == 0 ? b_low : b_low + 1;
}
void ADD_Split2::run(Executor &x) {
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

/* ADD_Change */
std::string ADD_Change::to_string() {
    std::ostringstream ss;
    ss << "ADD_Change(\n"
       << "    rd = " << rd << "\n"
       << "    rs1 = " << rs1 << "\n"
       << "    rs2 = " << rs2 << "\n"
       << "    a = " << a << "\n"
       << "    b = " << b << "\n"
       << ")";
    return ss.str();
}
void ADD_Change::randomize(Random &random) {
    rs1 = random.reg();
    rs2 = random.reg();
    rd = random.unique_reg({rs1, rs2, zero});
    a = random.reg_val();
    b = random.reg_val();
}
void ADD_Change::run(Executor &x) {
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
std::vector<std::shared_ptr<test_rule_if>> rules{
    std::make_shared<ADD_Comm>(),
    std::make_shared<ADD_Split>(),
    std::make_shared<ADD_Change>(),
    std::make_shared<ADD_Assoc>(),
    std::make_shared<ADD_Split2>(),
    std::make_shared<LX_AddrId<LoadInstr::LB>>(),
    std::make_shared<LX_AddrId<LoadInstr::LBU>>(),
    std::make_shared<LX_AddrId<LoadInstr::LH>>(),
    std::make_shared<LX_AddrId<LoadInstr::LHU>>(),
    std::make_shared<LX_AddrId<LoadInstr::LW>>(),
    std::make_shared<SX_LX_Id<1>>(),
    std::make_shared<SX_LX_Id<2>>(),
    std::make_shared<SX_LX_Id<4>>(),
    std::make_shared<LW_Combine2>(),
    std::make_shared<LHU_Combine2>(),
    std::make_shared<LX_ExtCheck<LoadInstr::LB>>(),
    std::make_shared<LX_ExtCheck<LoadInstr::LBU>>(),
    std::make_shared<LX_ExtCheck<LoadInstr::LH>>(),
    std::make_shared<LX_ExtCheck<LoadInstr::LHU>>(),
    std::make_shared<LXU_LX_Rel<1>>(),
    std::make_shared<LXU_LX_Rel<2>>(),
    std::make_shared<SW_RefCheck>(),
};
std::shared_ptr<test_rule_if> random_rule(Random &random) {
    return rules[random(rules.size())];
}
