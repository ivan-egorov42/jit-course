#include "ir/builder.h"

/**
 *   Source Code:
 *       function foo(value: int): int {
 *           let result = 1;
 *           for (let i = 2; i <= value; i++)
 *               result = result * i;
 *           }
 *           return result;
 *       }
 *
 *   IR Graph:
 *       BB_0:
 *           //entry
 *           0.s32 Param 228
 *       BB_1:
 *           1.s32 phi v4(BB_2), 1(BB_0)     // result
 *           2.s32 phi v5(BB_2), 2(BB_0)     // i
 *           3. if (v2 <= v0)
 *                goto BB_2 
 *              else
 *                goto BB_3
 *       BB_2:
 *           4.s32 mul v1, v2
 *           5.s32 add v2, 1
 *            goto BB_1
 *       BB_3:
 *           6.s32 ret v1
 */

int main() {
    auto cfg = new builder::CFG {};
    builder::Builder irbuilder(cfg);

    auto *bb0 = irbuilder.make_entry_bb();
    auto *bb1 = irbuilder.make_empty_bb(bb0);
    auto *bb2 = irbuilder.make_empty_bb(bb1);
    auto *bb3 = irbuilder.make_empty_bb(bb2);

    auto *v0 = irbuilder.build_int_param(228);
    auto *cst1 = irbuilder.build_int_cst(1);
    auto *cst2 = irbuilder.build_int_cst(2);

    auto *v1 = irbuilder.build_phi();
    v1->add_arg(bb0->get_id(), cst1);

    auto *v2 = irbuilder.build_phi();
    v1->add_arg(bb0->get_id(), cst2);

    auto *v3 = irbuilder.build_cond(builder::CondCode::LE_EXPR, v2, 0);

    bb1->add_phi(v1);
    bb1->add_phi(v2);
    bb1->add_inst_back(v3);

    auto *v4 = irbuilder.build_assign(builder::Opcode::MUL, v1, v2);
    auto *v5 = irbuilder.build_assign(builder::Opcode::ADD, v2, 1);

    auto *v6 = irbuilder.build_instruction(builder::Opcode::RET, v1);

    return 0;
}