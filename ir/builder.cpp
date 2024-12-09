#include "ir/cfg.h"
#include "ir/instruction.h"
#include "ir/basic-block.h"
#include "ir/common.h"
#include "builder.h"

namespace builder {
IntValue *Builder::build_int_cst(int value)
{
    return new IntValue(Type::INT_CST, value, nullptr);
}

IntParam *Builder::build_int_param(int param)
{
    return new IntParam(Type::INT_PARAM, param, nullptr);
}

Instruction *Builder::build_instruction(Opcode opcode, Instruction *op1)
{
    Instruction *inst =
        new Instruction(Type::INST, cfg->new_inst_id(), nullptr, nullptr, opcode, op1->get_ret_type(), nullptr);

    inst->add_input(op1, 0);

    return inst;
}

PhiInst *Builder::build_phi()
{
    return new PhiInst(Type::INST, cfg->new_inst_id(), nullptr, nullptr, Opcode::PHI, RetType::no_type, nullptr);
}

AssignInst *Builder::build_assign(Opcode opcode, Instruction *op1, Instruction *op2)
{
    if (op1->get_ret_type() != op2->get_ret_type())
        return nullptr;

    AssignInst *inst =
        new AssignInst(Type::INST, cfg->new_inst_id(), nullptr, nullptr, opcode, op1->get_ret_type(), nullptr);

    inst->add_input(op1, 0);
    inst->add_input(op2, 1);

    return inst;
}

AssignInst *Builder::build_assign(Opcode opcode, Instruction *op1, int op2)
{
    AssignInst *inst =
        new AssignInst(Type::INST, cfg->new_inst_id(), nullptr, nullptr, opcode, op1->get_ret_type(), nullptr);

    IntValue *cst = new IntValue(Type::INT_CST, op2, nullptr);

    inst->add_input(op1, 0);
    inst->add_input(cst, 1);

    return inst;
}

CondInst *Builder::build_cond(CondCode cond_code, Instruction *op1, int op2)
{
    CondInst *inst = new CondInst(Type::INST, cfg->new_inst_id(), nullptr, nullptr, Opcode::CMP, RetType::bool_t,
                                  nullptr, cond_code);

    IntValue *cst = new IntValue(Type::INT_CST, op2, nullptr);

    inst->add_input(op1, 0);
    inst->add_input(cst, 1);

    return inst;
}

BasicBlock *Builder::make_entry_bb()
{
    return cfg->make_entry();
}

BasicBlock *Builder::make_empty_bb(BasicBlock *after)
{
    BasicBlock *bb = new BasicBlock(false, cfg->new_bb_id(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, cfg);

    bb->add_pred(after);

    return bb;
}

void Builder::insert_seq_after(Instruction *inst, InstructionSeq *seq)
{
    BasicBlock *bb = inst->get_bb();
    assert(bb);
    // TODO: finish
}
}  // namespace builder