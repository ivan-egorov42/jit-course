#include <gtest/gtest.h>

#include "ir/domtree.h"
#include "ir/basic-block.h"
#include "ir/builder.h"

#include <set>

TEST(DOMTREE_tests, test1)
{
    auto *cfg = new builder::CFG {};
    builder::Builder irbuilder(cfg);

    auto *bb0 = irbuilder.make_entry_bb();
    auto *bb1 = irbuilder.make_empty_bb();
    auto *bb2 = irbuilder.make_empty_bb();
    auto *bb3 = irbuilder.make_empty_bb();
    auto *bb4 = irbuilder.make_empty_bb();
    auto *bb5 = irbuilder.make_empty_bb();
    auto *bb6 = irbuilder.make_empty_bb();

    bb0->set_true_succ(bb1);

    bb1->set_true_succ(bb2);
    bb1->set_false_succ(bb5);

    bb2->set_true_succ(bb3);

    bb4->set_true_succ(bb3);

    bb5->set_true_succ(bb4);
    bb5->set_false_succ(bb6);

    bb6->set_true_succ(bb3);

    builder::DominatorTree dom_tree(cfg);

    dom_tree.calculate_dom_tree(bb0);

    dom_tree.print_dominators();

    std::set<size_t> expected_doms_bb0 = {bb0->get_id()};
    std::set<size_t> expected_doms_bb1 = {bb0->get_id(), bb1->get_id()};
    std::set<size_t> expected_doms_bb2 = {bb0->get_id(), bb1->get_id(), bb2->get_id()};
    std::set<size_t> expected_doms_bb3 = {bb0->get_id(), bb1->get_id(), bb3->get_id()};
    std::set<size_t> expected_doms_bb4 = {bb0->get_id(), bb1->get_id(), bb4->get_id(), bb5->get_id()};
    std::set<size_t> expected_doms_bb5 = {bb0->get_id(), bb1->get_id(), bb5->get_id()};
    std::set<size_t> expected_doms_bb6 = {bb0->get_id(), bb1->get_id(), bb5->get_id(), bb6->get_id()};

    EXPECT_EQ(expected_doms_bb0, dom_tree.get_dominators_for(bb0->get_id()));
    EXPECT_EQ(expected_doms_bb1, dom_tree.get_dominators_for(bb1->get_id()));
    EXPECT_EQ(expected_doms_bb2, dom_tree.get_dominators_for(bb2->get_id()));
    EXPECT_EQ(expected_doms_bb3, dom_tree.get_dominators_for(bb3->get_id()));
    EXPECT_EQ(expected_doms_bb4, dom_tree.get_dominators_for(bb4->get_id()));
    EXPECT_EQ(expected_doms_bb5, dom_tree.get_dominators_for(bb5->get_id()));
    EXPECT_EQ(expected_doms_bb6, dom_tree.get_dominators_for(bb6->get_id()));
}

TEST(DOMTREE_tests, test2)
{
    auto *cfg = new builder::CFG {};
    builder::Builder irbuilder(cfg);

    auto *bb0 = irbuilder.make_entry_bb();
    auto *bb1 = irbuilder.make_empty_bb();
    auto *bb2 = irbuilder.make_empty_bb();
    auto *bb3 = irbuilder.make_empty_bb();
    auto *bb4 = irbuilder.make_empty_bb();
    auto *bb5 = irbuilder.make_empty_bb();
    auto *bb6 = irbuilder.make_empty_bb();
    auto *bb7 = irbuilder.make_empty_bb();
    auto *bb8 = irbuilder.make_empty_bb();
    auto *bb9 = irbuilder.make_empty_bb();
    auto *bb10 = irbuilder.make_empty_bb();

    bb0->set_true_succ(bb1);

    bb1->set_true_succ(bb2);
    bb1->set_false_succ(bb9);

    bb2->set_true_succ(bb3);

    bb3->set_true_succ(bb4);
    bb3->set_false_succ(bb2);

    bb4->set_true_succ(bb5);

    bb5->set_true_succ(bb6);
    bb5->set_false_succ(bb4);

    bb6->set_true_succ(bb7);
    bb6->set_false_succ(bb8);

    bb7->set_true_succ(bb1);

    bb8->set_true_succ(bb10);

    builder::DominatorTree dom_tree(cfg);

    dom_tree.calculate_dom_tree(bb0);

    dom_tree.print_dominators();
}

TEST(DOMTREE_tests, test3)
{
    auto *cfg = new builder::CFG {};
    builder::Builder irbuilder(cfg);

    auto *bb0 = irbuilder.make_entry_bb();
    auto *bb1 = irbuilder.make_empty_bb();
    auto *bb2 = irbuilder.make_empty_bb();
    auto *bb3 = irbuilder.make_empty_bb();
    auto *bb4 = irbuilder.make_empty_bb();
    auto *bb5 = irbuilder.make_empty_bb();
    auto *bb6 = irbuilder.make_empty_bb();
    auto *bb7 = irbuilder.make_empty_bb();
    auto *bb8 = irbuilder.make_empty_bb();
    auto *bb9 = irbuilder.make_empty_bb();
    auto *bb10 = irbuilder.make_empty_bb();

    bb0->set_true_succ(bb1);

    bb1->set_true_succ(bb2);
    bb1->set_false_succ(bb9);

    bb2->set_true_succ(bb3);

    bb3->set_true_succ(bb4);
    bb3->set_false_succ(bb2);

    bb4->set_true_succ(bb5);

    bb5->set_true_succ(bb6);
    bb5->set_false_succ(bb4);

    bb6->set_true_succ(bb7);
    bb6->set_false_succ(bb8);

    bb7->set_true_succ(bb1);

    bb8->set_true_succ(bb10);

    builder::DominatorTree dom_tree(cfg);

    dom_tree.calculate_dom_tree(bb0);

    dom_tree.print_dominators();
}