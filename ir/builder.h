#ifndef BUILDER_H
#define BUILDER_H

#include <vector>
#include "ir/common.h"

namespace builder {

class BasicBlock;
class Instruction;
class InstructionSeq;
class IntValue;
class IntParam;
class PhiInst;
class CondInst;
class AssignInst;
class CFG;

class Builder {
public:
    Builder(CFG *cfg) : cfg(cfg) {};

    CFG* get_cfg() {
      return cfg;
    }
    BasicBlock *make_entry_bb();
    BasicBlock *make_empty_bb();
    BasicBlock *make_empty_bb_after(BasicBlock *after, EdgeFlag flag);
    BasicBlock *make_bb(InstructionSeq *seq, BasicBlock *after);  // TODO:finish

    IntValue *build_int_cst(int value);
    IntParam *build_int_param(int param);

    Instruction *build_instruction(Opcode opcode, Instruction *op1);
    Instruction *build_instruction(Opcode opcode, Instruction *op1, Instruction *op2);
    AssignInst *build_assign(Opcode opcode, Instruction *op1, Instruction *op2);
    AssignInst *build_assign(Opcode opcode, Instruction *op1, int op2);

    PhiInst *build_phi();
    CondInst *build_cond(CondCode cond_code, Instruction *op1, Instruction *op2);
    CondInst *build_cond(CondCode cond_code, Instruction *op1, int op2);

    void insert_seq_after(Instruction *inst, InstructionSeq *seq);

private:
    CFG *cfg;
};

}  // namespace builder
#endif  // BUILDER_H