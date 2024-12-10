#ifndef CFG_H
#define CFG_H

#include <cstddef>
#include <cassert>
#include <unordered_map>

#include "ir/common.h"
#include "ir/basic-block.h"

namespace builder {

// class BasicBlock;
// class Edge;
// enum class EdgeFlag;

class CFG {
public:
    CFG() : current_bb_id(0), current_inst_id(0), entry_done(false), blocks_num(0) {};
    size_t new_bb_id()
    {
        return current_bb_id++;
    }
    size_t new_inst_id()
    {
        return current_inst_id++;
    }

    size_t size()
    {
        return blocks.size();
    }

    BasicBlock *make_entry()
    {
        assert(!entry_done);
        BasicBlock *entry_bb =
            new BasicBlock(true, new_bb_id(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, this);
        entry_done = true;
        entry = entry_bb;
        add_block(entry);
        return entry;
    }

    BasicBlock *get_entry()
    {
        return entry;
    }

    Edge *make_edge(BasicBlock *from, BasicBlock *to, EdgeFlag flag)
    {
        return new Edge(from, to, flag);
    }

    void add_block(BasicBlock *bb)
    {
        assert(entry_done);
        blocks[bb->get_id()] = bb;
        blocks_num++;
    }

    std::unordered_map<size_t, BasicBlock *>& get_blocks() {
      return blocks;
    }

private:
    size_t current_bb_id;
    size_t current_inst_id;
    bool entry_done;
    size_t blocks_num;

    // BBs blocks;
    std::unordered_map<size_t, BasicBlock *> blocks;
    BasicBlock *entry;
};
}  // namespace builder
#endif  // CFG_H