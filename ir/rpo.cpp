#include "ir/rpo.h"

namespace builder {

void RPO::run()
{
    size_t n = cfg->size();
    rpo_order.resize(n);
    visited.resize(n, false);

    calculate(cfg->get_entry(), n);
}

void RPO::calculate(BasicBlock *bb, size_t n)
{
    visited[bb->get_id()] = true;

    std::vector<BasicBlock *> succs = {bb->get_true_succ(), bb->get_false_succ()};
    for (auto succ : succs) {
        if (succ && !visited[succ->get_id()]) {
            calculate(succ, n);
        }
    }

    rpo_order[--n] = bb->get_id();
}

}  // namespace builder