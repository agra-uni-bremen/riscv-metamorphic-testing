#pragma once
#include <algorithm>
#include <boost/any.hpp>
#include <boost/tuple/tuple.hpp>
#include <sstream>
#include <string>
#include <vector>

#include "common.h"
#include "executor.h"
#include "instr.h"
#include "random.h"
#include <boost/algorithm/string.hpp>

// Map a name to a test attribute, such as a register or offset so that one can query these
// at runtime, for output, troubleshooting, etc.
#define ATTRIBUTE(NAME, CODE) add_attribute(#NAME, NAME = CODE);
// Add mutually exclusive registers to a test case, excluding x0/zero.
#define REGISTERS(r, ...) add_regs(r, #__VA_ARGS__, {__VA_ARGS__});
#define I_MASK 0xfff
#define SHAMT_MASK 0x1f

struct test_rule_if {
    typedef boost::tuple<std::string, boost::any> attr;
    std::vector<attr> attributes;
    virtual ~test_rule_if() {}
    virtual void run(Executor &x, Random &r) = 0;
    virtual std::string to_string();
    template <LoadInstr T>
    std::string to_string();
    /* Add a test attribute. */
    void add_attribute(std ::string name, boost::any value) {
        auto attr = boost::tuple<std::string, boost::any>(name, value);
        auto test = [name](auto t) { return boost::get<0>(t) == name; };
        auto pos = std::find_if(attributes.begin(), attributes.end(), test);
        if (pos != attributes.end()) {
            attributes.erase(pos);
        }
        attributes.push_back(attr);
    }
    /* Add mutually exclusive registers. 
       r: random instance
       rn: register names
       rp: register pointers
    */
    void add_regs(Random &r, std::string rn, std::initializer_list<unsigned*> rp) {
        std::vector<unsigned> taken = {zero};
        std::vector<std::string> names;
        rn.erase(remove_if(rn.begin(), rn.end(), boost::is_any_of("& ")), rn.end());
        boost::split(names, rn, boost::is_any_of(","));
        auto ri = rp.begin();
        for (auto n: names) {
            **ri = r.unique_reg(taken);
            add_attribute(n, **ri);
            taken.push_back(**ri);
            ri++;
        }
    }
};
std::shared_ptr<test_rule_if> random_rule(Random &r);
template <LoadInstr T>
std::string GetEnumName();
template <unsigned N>
int align_memory_addr(int reg, int off);
template <unsigned N>
int align_memory_addr(int addr);
template <LoadInstr T>
constexpr unsigned GetAlignWidth();