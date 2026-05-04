#ifndef ENGINE_EVAL_ARITHMETIC_H
#define ENGINE_EVAL_ARITHMETIC_H

#include "types.h"

/* Evaluator for the "arithmetic and constants" subset of the bytecode.
   Covers the opcodes:
   - CONST0..CONST3 (99-102), CONSTINT (103),
   - PUSHCONST0..PUSHCONST3 (104-107), PUSHCONSTINT (108),
   - NEGINT (109), ADDINT (110), SUBINT (111), MULINT (112),
   - DIVINT (113), MODINT (114),
   - ANDINT (115), ORINT (116), XORINT (117),
   - LSLINT (118), LSRINT (119), ASRINT (120),
   - LTINT (123), LEINT (124), GTINT (125), GEINT (126),
   - ULTINT (137), UGEINT (138),
   - OFFSETINT (127), ISINT (129). */
/* @requires mv points to a valid VM, instruction is the opcode at mv->codes[mv->pc]
   @assigns  mv->pc, mv->acc, mv->stack, mv->top (depending on which opcode is executed)
   @ensures  if instruction belongs to the "arithmetic" category, executes it via
             the local switch and returns 1; otherwise returns 0 without touching mv */
int engine_eval_arithmetic(vm *mv, int instruction);

#endif
