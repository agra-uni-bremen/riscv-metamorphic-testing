#include "mutations.h"

void ADD_Mutation1::apply(ISS &core) {
    auto x = core.read_reg(core.rs1()) - core.read_reg(core.rs2());
    core.write_reg(core.rd(), x);
}
void ADD_Mutation2::apply(ISS &core) {
    auto x = core.read_reg(core.rs1()) + core.read_reg(core.rs2()) + 1;
    core.write_reg(core.rd(), x);
}
void ADD_Mutation3::apply(ISS &core) {
    auto x = (core.read_reg(core.rs1()) + core.read_reg(core.rs2())) & ((1 << 30) - 1);
    core.write_reg(core.rd(), x);
}
std::vector<std::shared_ptr<exec_mutator_if>> mutators {
    std::make_shared<EmptyMutation>(),
    //std::make_shared<ADD_Mutation1>(),
    //std::make_shared<ADD_Mutation2>(),
    //std::make_shared<ADD_Mutation3>(),
};
std::vector<std::shared_ptr<exec_mutator_if>> get_mutators() {
    return mutators;
}
