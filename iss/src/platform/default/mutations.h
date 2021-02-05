#pragma once
#include "tests.h"

/* Common */
struct EmptyMutation : exec_mutator_if {
    bool exec(Opcode::Mapping op, ISS &core) override { return false; }
    void mutate_read_reg(Opcode::Mapping op, unsigned idx, int32_t &value) override {}
    void mutate_read_shamt(Opcode::Mapping op, unsigned idx, uint32_t &value) override {}
    void mutate_write_reg(Opcode::Mapping op, unsigned idx, int32_t &value) override {}
    void mutate_I_imm(Opcode::Mapping op, int32_t &I_imm) override {}
    void mutate_S_imm(Opcode::Mapping op, int32_t &S_imm) override {}
    void mutate_B_imm(Opcode::Mapping op, int32_t &B_imm) override {}
    void mutate_U_imm(Opcode::Mapping op, int32_t &U_imm) override {}
    void mutate_J_imm(Opcode::Mapping op, int32_t &J_imm) override {}
    void mutate_rs1(Opcode::Mapping op, unsigned &idx) override {}
    void mutate_rs2(Opcode::Mapping op, unsigned &idx) override {}
    void mutate_rd(Opcode::Mapping op, unsigned &idx) override {}
    void mutate_shamt(Opcode::Mapping op, unsigned &shamt) override {}
    void mutate_load_addr(Opcode::Mapping op, uint32_t &addr) override {}
    void mutate_load_value(Opcode::Mapping op, uint32_t addr, int32_t &value) override {}
    void mutate_store_access(Opcode::Mapping op, uint32_t &addr, uint32_t &value) override {}
    std::string name() override {
        return "Empty Mutation";
    }
};
std::vector<std::shared_ptr<exec_mutator_if>> get_mutators();
struct KilledMutation {
    std::shared_ptr<exec_mutator_if> mutator;
    std::string kill_test;
    unsigned num_iterations;
};
template <Opcode::Mapping TargetOp, typename Impl>
struct OperationMutation : EmptyMutation {
    std::string _name;
    OperationMutation(std::string name);
    bool exec(Opcode::Mapping op, ISS &core);
    void apply(ISS &core);
    std::string name();
};
template <Opcode::Mapping TargetOp, typename Impl>
OperationMutation<TargetOp, Impl>::OperationMutation(std::string name) {
    _name = name;
}
template <Opcode::Mapping TargetOp, typename Impl>
bool OperationMutation<TargetOp, Impl>::exec(Opcode::Mapping op, ISS &core) {
    if (op == TargetOp) {
        static_cast<Impl *>(this)->apply(core);
        return true;
    }
    return false;
}
template <Opcode::Mapping TargetOp, typename Impl>
std::string OperationMutation<TargetOp, Impl>::name() {
    return _name;
}

/* Mutations */
struct ADD_Mutation1 : OperationMutation<Opcode::ADD, ADD_Mutation1> {
    ADD_Mutation1() : OperationMutation<Opcode::ADD, ADD_Mutation1>("Add Mutation 1") {}
    void apply(ISS &core);
};
struct ADD_Mutation2 : OperationMutation<Opcode::ADD, ADD_Mutation2> {
    ADD_Mutation2() : OperationMutation<Opcode::ADD, ADD_Mutation2>("Add Mutation 2") {}
    void apply(ISS &core);
};
struct ADD_Mutation3 : OperationMutation<Opcode::ADD, ADD_Mutation3> {
    ADD_Mutation3() : OperationMutation<Opcode::ADD, ADD_Mutation3>("Add Mutation 3") {}
    void apply(ISS &core);
};