#ifndef DOMTREE_H
#define DOMTREE_H
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>

#include "ir/cfg.h"

namespace builder {

class DominatorTree {
public:
    DominatorTree(CFG *cfg) : cfg(cfg), n(cfg->size())
    {
        graph.resize(n);
        dominators.resize(n);
        init_graph();
    }

    void add_edge(size_t u, size_t v)
    {
        graph[u].push_back(v);
    }

    void init_graph()
    {
        std::unordered_map<size_t, BasicBlock *> &blocks = cfg->get_blocks();
        for (auto i = blocks.begin(); i != blocks.end(); i++) {
            BasicBlock *true_succ = i->second->get_true_succ();
            BasicBlock *false_succ = i->second->get_false_succ();

            if (true_succ)
                add_edge(i->first, true_succ->get_id());
            if (false_succ)
                add_edge(i->first, false_succ->get_id());
        }
    }

    void calculate_dom_tree(BasicBlock *entry)
    {
        for (size_t i = 0; i < n; ++i) {
            if (i == entry->get_id()) {
                dominators[i].insert(i);
            } else {
                for (size_t j = 0; j < n; ++j) {
                    dominators[i].insert(j);
                }
            }
        }

        bool changed = true;
        while (changed) {
            changed = false;

            for (size_t i = 0; i < n; ++i) {
                if (i == entry->get_id())
                    continue;

                std::set<size_t> newDominators;
                bool first = true;

                for (size_t pred : get_predecessors(i)) {
                    if (first) {
                        newDominators = dominators[pred];
                        first = false;
                    } else {
                        std::set<size_t> temp;
                        std::set_intersection(newDominators.begin(), newDominators.end(), dominators[pred].begin(),
                                              dominators[pred].end(), inserter(temp, temp.begin()));
                        newDominators = temp;
                    }
                }

                newDominators.insert(i);

                if (newDominators != dominators[i]) {
                    dominators[i] = newDominators;
                    changed = true;
                }
            }
        }
    }

    size_t get_imm_dom(BasicBlock *bb)
    {
        return bb != cfg->get_entry() ? *(++dominators[bb->get_id()].rbegin()) : -1;
    }

    size_t get_imm_dom(size_t id)
    {
        return id != cfg->get_entry()->get_id() ? *(++dominators[id].rbegin()) : -1;
    }

    std::vector<std::set<size_t>> &get_dominators()
    {
        return dominators;
    }

    std::set<size_t> &get_dominators_for(BasicBlock *bb)
    {
        return dominators[bb->get_id()];
    }

    std::set<size_t> &get_dominators_for(size_t id)
    {
        return dominators[id];
    }

    void print_dominators() const
    {
        for (size_t i = 0; i < n; ++i) {
            std::cout << "Node " << i << " is dominated by: ";
            for (size_t dom : dominators[i]) {
                std::cout << dom << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    CFG *cfg;
    size_t n;
    std::vector<std::vector<size_t>> graph;
    std::vector<std::set<size_t>> dominators;

    std::vector<size_t> get_predecessors(size_t node) const
    {
        std::vector<size_t> predecessors;
        for (size_t i = 0; i < n; ++i) {
            for (size_t neighbor : graph[i]) {
                if (neighbor == node) {
                    predecessors.push_back(i);
                }
            }
        }
        return predecessors;
    }
};

}  // namespace builder
#endif  // DOMTREE_H