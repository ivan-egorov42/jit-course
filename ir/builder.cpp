#include "ir/cfg.h"
#include "ir/instruction.h"
#include "ir/basic-block.h"
#include "ir/common.h"
#include "builder.h"

namespace builder {
IntValue *Builder::build_int_cst(int value)
{
    return new IntValue(Type::INT_CST, RetType::s32, value, nullptr);
}

IntParam *Builder::build_int_param(int param)
{
    return new IntParam(Type::INT_PARAM, RetType::s32, param, nullptr);
}

Instruction *Builder::build_instruction(Opcode opcode, Instruction *op1)
{
    Instruction *inst =
        new Instruction(Type::INST, cfg->new_inst_id(), nullptr, nullptr, opcode, op1->get_ret_type(), nullptr, 1);

    inst->add_input(op1, 0);

    return inst;
}

Instruction *Builder::build_instruction(Opcode opcode, Instruction *op1, Instruction *op2)
{
    Instruction *inst =
        new Instruction(Type::INST, cfg->new_inst_id(), nullptr, nullptr, opcode, op1->get_ret_type(), nullptr, 2);

    inst->add_input(op1, 0);
    inst->add_input(op2, 1);

    return inst;
}

PhiInst *Builder::build_phi()
{
    return new PhiInst(Type::INST, cfg->new_inst_id(), nullptr, nullptr, Opcode::PHI, RetType::no_type, nullptr, 0);
}

AssignInst *Builder::build_assign(Opcode opcode, Instruction *op1, Instruction *op2)
{
    if (op1->get_ret_type() != op2->get_ret_type())
        return nullptr;

    AssignInst *inst =
        new AssignInst(Type::INST, cfg->new_inst_id(), nullptr, nullptr, opcode, op1->get_ret_type(), nullptr, 2);

    inst->add_input(op1, 0);
    inst->add_input(op2, 1);

    return inst;
}

AssignInst *Builder::build_assign(Opcode opcode, Instruction *op1, int op2)
{
    AssignInst *inst =
        new AssignInst(Type::INST, cfg->new_inst_id(), nullptr, nullptr, opcode, op1->get_ret_type(), nullptr, 2);

    IntValue *cst = new IntValue(Type::INT_CST, RetType::s32, op2, nullptr);

    inst->add_input(op1, 0);
    inst->add_input(cst, 1);

    return inst;
}

CondInst *Builder::build_cond(CondCode cond_code, Instruction *op1, int op2)
{
    CondInst *inst = new CondInst(Type::INST, cfg->new_inst_id(), nullptr, nullptr, Opcode::CMP, RetType::bool_t,
                                  nullptr, cond_code, 2);

    IntValue *cst = new IntValue(Type::INT_CST, RetType::s32, op2, nullptr);

    inst->add_input(op1, 0);
    inst->add_input(cst, 1);

    return inst;
}

BasicBlock *Builder::make_entry_bb()
{
    return cfg->make_entry();
}

BasicBlock *Builder::make_empty_bb()
{
    BasicBlock *bb = new BasicBlock(false, cfg->new_bb_id(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, cfg);
    cfg->add_block(bb);

    return bb;
}

BasicBlock *Builder::make_empty_bb_after(BasicBlock *after, EdgeFlag flag)
{
    BasicBlock *bb = new BasicBlock(false, cfg->new_bb_id(), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, cfg);

    cfg->add_block(bb);
    bb->add_pred(after);

    switch (flag) {
        case EdgeFlag::FALLTHROUGH_EDGE:
            after->set_fallthru_succ(bb);
        case EdgeFlag::TRUE_EDGE:
            after->set_true_succ(bb);
        case EdgeFlag::FALSE_EDGE:
            after->set_false_succ(bb);
    }

    return bb;
}

void Builder::insert_seq_after(Instruction *inst, InstructionSeq *seq)
{
    BasicBlock *bb = inst->get_bb();
    assert(bb);
    // TODO: finish
}
}  // namespace builder