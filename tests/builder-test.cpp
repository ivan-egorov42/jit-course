#include <gtest/gtest.h>

#include "ir/builder.h"
#include "ir/cfg.h"
#include "ir/instruction.h"
#include "ir/basic-block.h"

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
 *             goto BB_1
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

TEST(IR_BUILDER, Factorial)
{
    auto *cfg = new builder::CFG {};
    builder::Builder irbuilder(cfg);

    auto *bb0 = irbuilder.make_entry_bb();
    auto *bb1 = irbuilder.make_empty_bb_after(bb0, builder::EdgeFlag::FALLTHROUGH_EDGE);
    auto *bb2 = irbuilder.make_empty_bb_after(bb1, builder::EdgeFlag::TRUE_EDGE);
    auto *bb3 = irbuilder.make_empty_bb_after(bb1, builder::EdgeFlag::FALSE_EDGE);

    auto *v0 = irbuilder.build_int_param(228);
    auto *cst1 = irbuilder.build_int_cst(1);
    auto *cst2 = irbuilder.build_int_cst(2);

    auto *v1 = irbuilder.build_phi();
    v1->add_arg(bb0->get_id(), cst1);

    auto *v2 = irbuilder.build_phi();
    v2->add_arg(bb0->get_id(), cst2);

    auto *v3 = irbuilder.build_cond(builder::CondCode::LE_EXPR, v2, 228);

    bb1->add_phi(v1);
    bb1->add_phi(v2);
    bb1->add_inst_back(v3);

    auto *v4 = irbuilder.build_assign(builder::Opcode::MUL, v1, v2);
    auto *v5 = irbuilder.build_assign(builder::Opcode::ADD, v2, 1);

    v1->add_arg(bb2->get_id(), v4);
    v2->add_arg(bb2->get_id(), v5);

    bb2->add_inst_back(v4);
    bb2->add_inst_back(v5);

    auto *v6 = irbuilder.build_instruction(builder::Opcode::RET, v1);

    bb3->add_inst_back(v6);

    bb0->set_fallthru_succ(bb1);
    auto *e1 = cfg->make_edge(bb0, bb1, builder::EdgeFlag::FALLTHROUGH_EDGE);

    bb1->set_true_succ(bb2);
    bb1->set_false_succ(bb3);
    auto *e2 = cfg->make_edge(bb1, bb2, builder::EdgeFlag::TRUE_EDGE);
    auto *e3 = cfg->make_edge(bb1, bb3, builder::EdgeFlag::FALSE_EDGE);

    bb2->set_fallthru_succ(bb1);

    bb1->add_pred(bb0);
    bb1->add_pred(bb2);
    bb2->add_pred(bb1);
    bb3->add_pred(bb1);

    cfg->add_block(bb0);
    cfg->add_block(bb1);
    cfg->add_block(bb2);
    cfg->add_block(bb3);

    ASSERT_EQ(v1->get_opcode(), builder::Opcode::PHI);
    ASSERT_EQ(v2->get_opcode(), builder::Opcode::PHI);
    ASSERT_EQ(v1->get_arg(bb0->get_id()), cst1);
    ASSERT_EQ(v2->get_arg(bb0->get_id()), cst2);
    ASSERT_EQ(v3->get_cond_code(), builder::CondCode::LE_EXPR);
    ASSERT_EQ(v3->get_opcode(), builder::Opcode::CMP);
    ASSERT_EQ(bb1->get_first_phi(), v1);
    ASSERT_EQ(bb1->get_last_phi(), v2);
    ASSERT_EQ(bb1->get_last_inst(), v3);
    ASSERT_EQ(bb1->get_first_inst(), v3);
    ASSERT_EQ(v4->get_opcode(), builder::Opcode::MUL);
    ASSERT_EQ(v5->get_opcode(), builder::Opcode::ADD);
    ASSERT_EQ(v3->get_inputs()[0], v2);
    ASSERT_EQ(v4->get_inputs()[0], v1);
    ASSERT_EQ(v4->get_inputs()[1], v2);
    ASSERT_EQ(v5->get_inputs()[0], v2);
    ASSERT_EQ(v1->get_arg(bb2->get_id()), v4);
    ASSERT_EQ(v2->get_arg(bb2->get_id()), v5);
    ASSERT_EQ(bb2->get_last_inst(), v5);
    ASSERT_EQ(bb2->get_first_inst(), v4);
    ASSERT_EQ(v6->get_opcode(), builder::Opcode::RET);
    ASSERT_EQ(bb3->get_first_inst(), v6);
    ASSERT_EQ(bb3->get_last_inst(), v6);
    ASSERT_EQ(bb1->get_true_succ(), bb2);
    ASSERT_EQ(bb1->get_false_succ(), bb3);
    ASSERT_EQ(bb1->get_preds()[0], bb0);
}