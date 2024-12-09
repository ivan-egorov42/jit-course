#ifndef COMMON_H
#define COMMON_H

#include <cstddef>

namespace builder {

constexpr size_t invalid_id = -1;

enum class Opcode {
    ADD = 0,
    MUL = 1,
    JMP = 2,
    RET = 3,
    CONST = 4,
    ASSIGN = 5,
    CAST = 6,
    CMP = 7,
    PHI = 8,
    INVALID = 9
};

enum class CondCode { LT_EXPR = 0, LE_EXPR = 1, GT_EXPR = 2, GE_EXPR = 3, EQ_EXPR = 4, NE_EXPR = 5, INVALID = 6 };

enum class RetType { no_type = 0, u32 = 1, u64 = 2, s32 = 3, s64 = 4, bool_t = 5 };

enum class Type { INT_CST = 0, INT_PARAM = 1, INST = 2 };

enum class EdgeFlag { TRUE_EDGE, FALSE_EDGE, FALLTHROUGH_EDGE };

}  // namespace builder
#endif  // COMMON_H