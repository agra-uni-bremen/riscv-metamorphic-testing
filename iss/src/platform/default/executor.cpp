#include "executor.h"
#include "memory_interface.h"
#include "test_rules.h"

Executor::Executor(ISS &core, Random &random, RandomLazyMemory &mem)
    : DefaultLoadStoreMemoryInterface(mem), core(core), random(random) {
    core.instr_mem = this;
    core.mem = this;
}
uint32_t Executor::load_instr(uint64_t addr) { 
    return code.next(); 
}
uint32_t Executor::run(unsigned rd) {
    assert(code.has_next());
    while (code.has_next()) {
        core.run_step();
    }
    code.clear();
    return core.regs[rd];
}
uint32_t Executor::get_reg(unsigned idx) { 
    return core.regs[idx]; 
}
void Executor::check(bool cond) {
    if (!cond) throw RuleCheckFailed("ERROR: rule check failed");
}
