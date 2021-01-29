#include "executor.h"
#include "mutations.h"
#include "test_rules.h"

int main(int argc, char **argv) {
    constexpr unsigned max_iterations_per_mutant = 100000;
    std::vector<KilledMutation> killed_mutations;
    ISS core(0, false);
    Random random;
    RandomLazyMemory mem(random);
    Executor exec(core, random, mem);
    core.randomize_state();
    // core.trace = true;
    auto mutators = get_mutators();
    for (auto m : mutators) {
        std::cout << "> check mutator: " << m->name() << std::endl;
        core.mutator = m.get();
        unsigned i;
        std::shared_ptr<test_rule_if> rule;
        try {
            for (i = 0; i < max_iterations_per_mutant; ++i) {
                rule = random_rule(random);
                rule->randomize(random);
                rule->run(exec);
            }
        } catch (RuleCheckFailed &e) {
            killed_mutations.push_back({m, rule->to_string(), i + 1});
        }
    }
    std::cout << std::endl;
    core.show();
    std::cout << std::endl;
    for (unsigned k = 0; k < killed_mutations.size(); ++k) {
        auto &e = killed_mutations[k];
        std::cout << "[" << k + 1 << "] killed mutation: " << e.mutator->name()
                  << ", by rule: " << e.kill_test << " after "
                  << e.num_iterations << " iterations\n"
                  << std::endl;
    }
    std::cout << "total killed mutations: " << killed_mutations.size() << " / " << mutators.size() << std::endl;
    return 0;
}
