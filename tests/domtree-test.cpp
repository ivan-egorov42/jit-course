#include <gtest/gtest.h>

#include "ir/domtree.h"
#include "ir/basic-block.h"
#include "ir/builder.h"

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

    builder::DominatorTree domTree(cfg);

    domTree.calculate_dom_tree(bb0);

    domTree.printDominators();
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

    builder::DominatorTree domTree(cfg);

    domTree.calculate_dom_tree(bb0);

    domTree.printDominators();
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

    builder::DominatorTree domTree(cfg);

    domTree.calculate_dom_tree(bb0);

    domTree.printDominators();
}