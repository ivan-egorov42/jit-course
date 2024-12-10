#include "ir/rpo.h"

namespace builder {

void RPO::run()
{
    n = cfg->size();
    rpo_order.resize(n, -1);
    visited.resize(n, false);

    calculate(cfg->get_entry());
}

void RPO::calculate(BasicBlock *bb)
{
    visited[bb->get_id()] = true;

    std::vector<BasicBlock *> succs = {bb->get_true_succ(), bb->get_false_succ()};
    for (auto succ : succs) {
        if (succ && !visited[succ->get_id()]) {
            calculate(succ);
        }
    }

    rpo_order[--n] = bb->get_id();
}

}  // namespace builder