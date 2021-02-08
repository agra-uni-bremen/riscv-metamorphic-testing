#include "mutations.h"

/* Mutations */
struct ADD_Mutation1 : OperationMutation<Opcode::ADD, ADD_Mutation1> {
    ADD_Mutation1() : OperationMutation<Opcode::ADD, ADD_Mutation1>("Add 1") {}
    void apply(ISS &core) {
        auto x = core.read_reg(core.rs1()) - core.read_reg(core.rs2());
        core.write_reg(core.rd(), x);
    }
};
struct ADD_Mutation2 : OperationMutation<Opcode::ADD, ADD_Mutation2> {
    ADD_Mutation2() : OperationMutation<Opcode::ADD, ADD_Mutation2>("Add 2") {}
    void apply(ISS &core) {
        auto x = core.read_reg(core.rs1()) + core.read_reg(core.rs2()) + 1;
        core.write_reg(core.rd(), x);
    }
};
struct ADD_Mutation3 : OperationMutation<Opcode::ADD, ADD_Mutation3> {
    ADD_Mutation3() : OperationMutation<Opcode::ADD, ADD_Mutation3>("Add 3") {}
    void apply(ISS &core) {
        auto x = (core.read_reg(core.rs1()) + core.read_reg(core.rs2())) & ((1 << 30) - 1);
        core.write_reg(core.rd(), x);
    }
};
struct AND_Mutation1 : OperationMutation<Opcode::ADD, AND_Mutation1> {
    AND_Mutation1() : OperationMutation<Opcode::ADD, AND_Mutation1>("AND & to |") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) | core.read_reg(core.rs2()));
    }
};
struct BLT_Mutation1 : OperationMutation<Opcode::BLT, BLT_Mutation1> {
    BLT_Mutation1() : OperationMutation<Opcode::BLT, BLT_Mutation1>("BLT < to <=") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) <= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
struct BLT_Mutation2 : OperationMutation<Opcode::BLT, BLT_Mutation2> {
    BLT_Mutation2() : OperationMutation<Opcode::BLT, BLT_Mutation2>("BLT < to >") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) > core.read_reg(core.rs2())) {
            printf("M: %X %X\n", core.read_reg(core.rs1()), core.read_reg(core.rs2()));
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
struct BGE_Mutation1 : OperationMutation<Opcode::BGE, BGE_Mutation1> {
    BGE_Mutation1() : OperationMutation<Opcode::BGE, BGE_Mutation1>("BGE >= to <=") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs1()) <= core.read_reg(core.rs2())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
struct BGE_Mutation2 : OperationMutation<Opcode::BGE, BGE_Mutation2> {
    BGE_Mutation2() : OperationMutation<Opcode::BGE, BGE_Mutation2>("BGE >= to <=") {}
    void apply(ISS &core) {
        if (core.read_reg(core.rs2()) >= core.read_reg(core.rs1())) {
            core.pc = core.last_pc + core.B_imm();
            core.trap_check_pc_alignment();
        }
    }
};
struct SLL_Mutation1 : OperationMutation<Opcode::SLL, SLL_Mutation1> {
    SLL_Mutation1() : OperationMutation<Opcode::SLL, SLL_Mutation1>("SLL << to >>") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) >> core.regs.shamt(core.rs2()));
    }
};
struct SRL_Mutation1 : OperationMutation<Opcode::SRL, SRL_Mutation1> {
    SRL_Mutation1() : OperationMutation<Opcode::SRL, SRL_Mutation1>("SRL >> to <<") {}
    void apply(ISS &core) {
        core.write_reg(core.rd(), core.read_reg(core.rs1()) << core.regs.shamt(core.rs2()));
    }
};
struct JAL_Mutation1 : OperationMutation<Opcode::JAL, JAL_Mutation1> {
    JAL_Mutation1() : OperationMutation<Opcode::JAL, JAL_Mutation1>("JAL + to -") {}
    void apply(ISS &core) {
        auto link = core.pc;
        core.pc = core.last_pc - core.J_imm();
        core.trap_check_pc_alignment();
        core.write_reg(core.rd(), link);
    }
};
std::vector<std::shared_ptr<exec_mutator_if>> mutators{
    std::make_shared<EmptyMutation>(),
    std::make_shared<ADD_Mutation1>(),
    std::make_shared<ADD_Mutation2>(),
    std::make_shared<ADD_Mutation3>(),
    std::make_shared<AND_Mutation1>(),
    std::make_shared<BGE_Mutation1>(),
    std::make_shared<BGE_Mutation2>(),
    std::make_shared<BLT_Mutation1>(),
    std::make_shared<BLT_Mutation2>(),
    std::make_shared<JAL_Mutation1>(),
    std::make_shared<SLL_Mutation1>(),
    std::make_shared<SRL_Mutation1>(),
};
std::vector<std::shared_ptr<exec_mutator_if>> mutators_{
    std::make_shared<EmptyMutation>(),
    std::make_shared<SLL_Mutation1>(),
    std::make_shared<SRL_Mutation1>(),
};
std::vector<std::shared_ptr<exec_mutator_if>> get_mutators() {
    return mutators;
}
