#ifndef BASIC_BLOCK_H
#define BASIC_BLOCK_H

#include <iostream>
#include <vector>
#include <cassert>

#include "cfg.h"
#include "instruction.h"

namespace builder {

using BBs = std::vector<BasicBlock*>;

class CFG;

class BasicBlock 
{
public:
  BasicBlock () = default;
  BasicBlock (bool is_entry, size_t id, BasicBlock* true_succ, BasicBlock* false_succ, Instruction* first_phi, Instruction* last_phi, Instruction* first_inst, Instruction* last_inst, CFG* cfg) : is_entry(is_entry), id(id), true_succ(true_succ), false_succ(false_succ), first_phi(first_phi), last_phi(last_phi), first_inst(first_inst), last_inst(last_inst), cfg(cfg) {}

  size_t get_id() const { return id;}
  const BasicBlock* get_true_succ() const { return true_succ;}
  const BasicBlock* get_false_succ() const { return false_succ;}

  void add_pred(BasicBlock* pred) {
    preds.push_back(pred);
  }

  Instruction* add_inst_back (Instruction* inst) {
    assert (!inst->get_prev() && !inst->get_next());

    inst->set_bb(this);

    if (!last_inst)
      {
        if (last_phi) {
          inst->set_prev(last_phi);
          last_phi->set_next(first_inst);
        }
        last_inst = inst;
        first_inst = last_inst;
        return last_inst;
      }

    // last_inst->get_next()->set_prev(inst);
    last_inst->set_next(inst);
    inst->set_prev(last_inst);
    last_inst = inst;

    return last_inst;
  }

  Instruction* add_phi (PhiInst* phi) {
    assert (!phi->get_prev() && !phi->get_next());

    phi->set_bb(this);

    if (!first_phi)
    {
      if (first_inst) {
        phi->set_next(first_inst);
        first_inst->set_prev(phi); 
      }

      first_phi = phi;
      last_phi = first_phi;

      return first_phi;
    }

    last_phi->set_next(phi);
    phi->set_prev(last_phi);
    phi->set_next(first_inst);
    first_inst->set_prev(last_phi);
    last_phi = phi;

    return last_phi;
  }


  const Instruction* get_first_inst () { return first_inst;}
  const Instruction* get_last_inst () { return last_inst;}

private:
  bool is_entry;
  size_t id;

  BBs preds;
  BasicBlock* true_succ;
  BasicBlock* false_succ;

  Instruction* first_phi;
  Instruction* last_phi;
  Instruction* first_inst;
  Instruction* last_inst;

  CFG* cfg;
};

class Edge 
{
public:
  Edge() : src(nullptr), dest(nullptr) {};

private:
  BasicBlock* src;
  BasicBlock* dest;

};
} // namespace builder
#endif // BASIC_BLOCK_H