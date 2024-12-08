#ifndef CFG_H
#define CFG_H

#include "basic-block.h"

#include <vector>
namespace builder {

class CFG
{
public:
  CFG () : current_bb_id(0), current_inst_id(0) {};
  size_t new_bb_id () {return current_bb_id++;}
  size_t new_inst_id () {return current_inst_id++;}

  BasicBlock* make_entry () {
    return new BasicBlock(true, new_bb_id (), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, this);
  }

private:
  size_t current_bb_id;
  size_t current_inst_id;

};
}// namespace builder
#endif // CFG_H