#ifndef RPO_H
#define RPO_H
#include <vector>
#include <cstddef>

#include "cfg.h"
#include "basic-block.h"

namespace builder {

class RPO {
public:
    RPO(CFG *cfg) : cfg(cfg) {}
    void run();
    void calculate(BasicBlock *bb, size_t n);
    std::vector<size_t> get_order()
    {
        return rpo_order;
    }

private:
    CFG *cfg;
    std::vector<size_t> rpo_order;
    std::vector<bool> visited;
};

}  // namespace builder
#endif  // RPO_H