#pragma once
#include "code_builder.h"
#include "core/rv32/iss.h"
#include "memory_interface.h"

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
