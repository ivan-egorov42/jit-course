#include "ir/cfg.h"
#include "ir/instruction.h"
#include "ir/basic-block.h"

namespace builder {

Instruction *BasicBlock::add_inst_back(Instruction *inst)
{
    assert(!inst->get_prev() && !inst->get_next());

    inst->set_bb(this);

    if (!last_inst) {
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

Instruction *BasicBlock::add_inst_after(Instruction *inst, Instruction *after)
{
    assert(!inst->get_prev() && !inst->get_next());
    if (after->get_bb() != this)
        return nullptr;

    inst->set_bb(this);
    inst->set_prev(after);
    inst->set_next(after->get_next());
    after->get_next()->set_prev(inst);
    after->set_next(inst);

    return inst;
}

PhiInst *BasicBlock::add_phi(PhiInst *phi)
{
    assert(!phi->get_prev() && !phi->get_next());

    phi->set_bb(this);

    if (!first_phi) {
        if (first_inst) {
            phi->set_next(first_inst);
            first_inst->set_prev(phi);
        }

        first_phi = phi;
        last_phi = first_phi;

        return first_phi;
    }

    if (first_inst) {
        phi->set_next(first_inst);
        first_inst->set_prev(phi);
    }

    last_phi->set_next(phi);
    phi->set_prev(last_phi);
    // phi->set_next(first_inst);
    //  first_inst->set_prev(last_phi);
    last_phi = phi;

    return last_phi;
}
}  // namespace builder