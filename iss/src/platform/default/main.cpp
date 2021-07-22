#include <map>
#include <vector>

#include "common.h"
#include "executor.h"
#include "mutations.h"
#include "tests.h"

template <typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B> &p) {
    return std::pair<B, A>(p.second, p.first);
}

template <typename A, typename B>
std::multimap<B, A> flip_map(const std::map<A, B> &src) {
    std::multimap<B, A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), flip_pair<A, B>);
    return dst;
}

int main(int argc, char **argv) {
    //srand(time(NULL));
    constexpr unsigned max_iterations_per_mutant = 1000000;
    std::vector<KilledMutation> killed;
    std::map<std::string, int> stats;
    ISS core(0, false);
    Random random;
    RandomLazyMemory mem(random);
    Executor exec(core, random, mem);
    core.randomize_state();
    core.trace = false;
    auto mutators = get_mutators();
    for (auto m : mutators) {
        std::cout << "> check mutator: " << m->name() << " ...";
        core.mutator = m.get();
        unsigned i;
        std::shared_ptr<test_rule_if> rule;
        std::string name;
        bool live = true;
        try {
            for (i = 1; i <= max_iterations_per_mutant; ++i) {
                rule = random_rule(random);
                name = abi::__cxa_demangle(typeid(*rule).name(), 0, 0, 0);
                rule->run(exec, random);
                if (stats[name] == 0) {
                    stats[name] = 0;
                }
            }
        } catch (const RuleCheckFailed &e) {
            killed.push_back({m, rule->to_string(), i + 1});
            stats[name]++;
            live = false;
            
        } catch (const TraceableException &e) {
            std::cout << "Exception during test run: " << e.what();
        }

        if (live) {
            std::cout << " survived." << std::endl;
        } else {
            std::cout << " killed after " << i << " iterations by:" << std::endl;
            std::cout << rule->to_string();
        }
    }
    for (auto m : mutators) {
        auto test = [m](auto k) { return m->name() == k.mutator->name(); };
        if (std::find_if(killed.begin(), killed.end(), test) == killed.end()) {
            std::cout << "Unkilled mutation '" << m->name() << "'." << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "total killed mutations: " << killed.size() << " / " << mutators.size() << std::endl;
    std::cout << "Test statistics:" << std::endl;
    std::multimap<int, std::string> dst = flip_map(stats);
    for (auto e : dst) {
        std::cout << std::get<1>(e) << ": " << std::get<0>(e) << std::endl;
    }
    return 0;
}
