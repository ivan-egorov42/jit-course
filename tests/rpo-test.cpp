#include <gtest/gtest.h>

#include "ir/rpo.h"
#include "ir/basic-block.h"
#include "ir/builder.h"

TEST(RPOTest, RPO1) {
    auto *cfg = new builder::CFG {};
    builder::Builder irbuilder(cfg);
  auto* A = irbuilder.make_entry_bb();
  auto* B = irbuilder.make_empty_bb();
  auto* C = irbuilder.make_empty_bb();
  auto* D = irbuilder.make_empty_bb();
  auto* E = irbuilder.make_empty_bb();
  auto* F = irbuilder.make_empty_bb();
  auto* G = irbuilder.make_empty_bb();
  auto* H = irbuilder.make_empty_bb();
  auto* I = irbuilder.make_empty_bb();
  auto* K = irbuilder.make_empty_bb();
  auto* L = irbuilder.make_empty_bb();
  auto* O = irbuilder.make_empty_bb();
  auto* Q = irbuilder.make_empty_bb();
  auto* R = irbuilder.make_empty_bb();
  auto* T = irbuilder.make_empty_bb();
  auto* V = irbuilder.make_empty_bb();
  auto* W = irbuilder.make_empty_bb();
  auto* X = irbuilder.make_empty_bb();

  A->set_true_succ(B);
  B->set_true_succ(C);
  C->set_true_succ(D);
  C->set_false_succ(R);
  D->set_true_succ(E);
  E->set_true_succ(F);
  E->set_false_succ(L);
  F->set_true_succ(H);
  F->set_false_succ(G);
  G->set_true_succ(Q);
  H->set_true_succ(T);
  H->set_false_succ(O);
  I->set_true_succ(A);
  K->set_true_succ(A);
  L->set_true_succ(I);
  O->set_true_succ(E);
  Q->set_true_succ(W);
  R->set_true_succ(B);
  T->set_true_succ(V);
  V->set_true_succ(X);
  V->set_false_succ(K);
  W->set_true_succ(A);

  builder::RPO rpo(cfg);
  rpo.run();

  std::vector<size_t> rpo_order = rpo.get_order();

  std::vector<size_t> expected_rpo_order = {B->get_id(),
                                           R->get_id(),
                                           A->get_id(),
                                           I->get_id(),
                                           L->get_id(),
                                           W->get_id(),
                                           Q->get_id(),
                                           G->get_id(),
                                           E->get_id(),
                                           O->get_id(),
                                           K->get_id(),
                                           X->get_id(),
                                           V->get_id(),
                                           T->get_id(),
                                           H->get_id(),
                                           F->get_id(),
                                           D->get_id(),
                                           C->get_id()};

  EXPECT_EQ(rpo_order.size(), expected_rpo_order.size());

  for (size_t i = 0; i < rpo_order.size(); ++i) {
    EXPECT_EQ(rpo_order[i], expected_rpo_order[i]);
  }

  delete cfg;
}