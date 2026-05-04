#ifndef ENGINE_EVAL_BASE_H
#define ENGINE_EVAL_BASE_H

#include "types.h"

/* Evaluator for the "base instructions" subset of the bytecode.
   Covers opcodes 0 through 20 inclusive:
   ACC0..ACC7 (0-7), ACC (8), PUSH (9), PUSHACC0..PUSHACC7 (10-17),
   PUSHACC (18), POP (19), ASSIGN (20). */
/* @requires mv points to a valid VM, instruction is the opcode at mv->codes[mv->pc]
   @assigns  mv->pc, mv->acc, mv->stack, mv->top (depending on which opcode is executed)
   @ensures  if instruction belongs to the "base" category, executes it via the
             local switch and returns 1; otherwise returns 0 without touching mv */
int engine_eval_base(vm *mv, int instruction);

#endif
