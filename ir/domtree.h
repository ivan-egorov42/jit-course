#ifndef DOMTREE_H
#define DOMTREE_H
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include "ir/cfg.h"

namespace builder {

class DominatorTree {
public:
    DominatorTree(CFG *cfg) : cfg(cfg), n(cfg->size())
    {
        graph.resize(n);
        dominators.resize(n);
    }

    void add_edge(int u, int v)
    {
        graph[u].push_back(v);
    }

    void calculate_dom_tree(BasicBlock *entry)
    {
        for (int i = 0; i < n; ++i) {
            if (i == entry->get_id()) {
                dominators[i].insert(i);
            } else {
                for (int j = 0; j < n; ++j) {
                    dominators[i].insert(j);
                }
            }
        }

        bool changed = true;
        while (changed) {
            changed = false;

            for (int i = 0; i < n; ++i) {
                if (i == entry->get_id())
                    continue;

                std::set<int> newDominators;
                bool first = true;

                for (int pred : get_predecessors(i)) {
                    if (first) {
                        newDominators = dominators[pred];
                        first = false;
                    } else {
                        std::set<int> temp;
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

    void printDominators() const
    {
        for (int i = 0; i < n; ++i) {
            cout << "Node " << i << " is dominated by: ";
            for (int dom : dominators[i]) {
                cout << dom << " ";
            }
            cout << endl;
        }
    }

private:
    CFG *cfg;
    int n;
    std::vector<std::vector<int>> graph;
    std::vector<std::set<int>> dominators;

    std::vector<int> get_predecessors(int node) const
    {
        std::vector<int> predecessors;
        for (int i = 0; i < n; ++i) {
            for (int neighbor : graph[i]) {
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