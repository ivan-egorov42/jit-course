#ifndef BASIC_BLOCK_H
#define BASIC_BLOCK_H

// #include <iostream>
#include <vector>
#include <cassert>
#include <cstddef>

#include "ir/common.h"

namespace builder {

class CFG;
class Instruction;
class PhiInst;
class BasicBlock;

using BBs = std::vector<BasicBlock *>;

class BasicBlock {
public:
    BasicBlock() = default;
    BasicBlock(bool is_entry, size_t id, BasicBlock *true_succ, BasicBlock *false_succ, PhiInst *first_phi,
               PhiInst *last_phi, Instruction *first_inst, Instruction *last_inst, CFG *cfg)
        : is_entry(is_entry),
          id(id),
          true_succ(true_succ),
          false_succ(false_succ),
          first_phi(first_phi),
          last_phi(last_phi),
          first_inst(first_inst),
          last_inst(last_inst),
          cfg(cfg)
    {
    }

    size_t get_id() const
    {
        return id;
    }
    BasicBlock *get_true_succ() const
    {
        return true_succ;
    }
    BasicBlock *get_false_succ() const
    {
        return false_succ;
    }

    void set_true_succ(BasicBlock *bb)
    {
        true_succ = bb;
    }
    void set_false_succ(BasicBlock *bb)
    {
        false_succ = bb;
    }
    void set_fallthru_succ(BasicBlock *bb)
    {
        true_succ = bb;
    }

    void add_pred(BasicBlock *pred)
    {
        preds.push_back(pred);
    }
    BBs get_preds()
    {
        return preds;
    }

    Instruction *add_inst_back(Instruction *inst);
    PhiInst *add_phi(PhiInst *phi);

    const Instruction *get_first_inst()
    {
        return first_inst;
    }
    const Instruction *get_last_inst()
    {
        return last_inst;
    }

    const PhiInst *get_first_phi()
    {
        return first_phi;
    }

    const PhiInst *get_last_phi()
    {
        return last_phi;
    }

private:
    bool is_entry;
    size_t id;

    BBs preds;
    BasicBlock *true_succ;
    BasicBlock *false_succ;

    PhiInst *first_phi;
    PhiInst *last_phi;
    Instruction *first_inst;
    Instruction *last_inst;

    CFG *cfg;
};

class Edge {
public:
    Edge() : src(nullptr), dest(nullptr) {};
    Edge(BasicBlock *src, BasicBlock *dest, EdgeFlag flag) : src(src), dest(dest), flag(flag) {}

    EdgeFlag get_flag()
    {
        return flag;
    }

private:
    BasicBlock *src;
    BasicBlock *dest;

    EdgeFlag flag;
};
}  // namespace builder
#endif  // BASIC_BLOCK_H