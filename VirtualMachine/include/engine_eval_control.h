#ifndef ENGINE_EVAL_CONTROL_H
#define ENGINE_EVAL_CONTROL_H

#include "types.h"

/* Evaluator for the "control flow and primitive calls" subset of the bytecode.
   Covers the opcodes:
   - STOP (143), CHECK_SIGNALS (92),
   - BRANCH (84), BRANCHIF (85), BRANCHIFNOT (86), SWITCH (87),
   - BOOLNOT (88), EQ (121), NEQ (122),
   - BEQ (131), BNEQ (132),
   - BLTINT (133), BLEINT (134), BGTINT (135), BGEINT (136),
   - BULTINT (139), BUGEINT (140),
   - C_CALL1..C_CALL5 (93-97), C_CALLN (98). */
/* @requires mv points to a valid VM, instruction is the opcode at mv->codes[mv->pc]
   @assigns  mv->pc, mv->acc, mv->stack, mv->top, mv->running (depending on the opcode)
   @ensures  if instruction belongs to the "control" category, executes it via the
             local switch and returns 1; otherwise returns 0 without touching mv */
int engine_eval_control(vm *mv, int instruction);

#endif
