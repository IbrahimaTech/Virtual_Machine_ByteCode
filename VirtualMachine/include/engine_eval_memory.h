#ifndef ENGINE_EVAL_MEMORY_H
#define ENGINE_EVAL_MEMORY_H

#include "types.h"

/* Evaluator for the "memory, blocks, globals and atoms" subset of the bytecode.
   Covers the opcodes:
   - GETGLOBAL (53), PUSHGETGLOBAL (54), SETGLOBAL (57),
   - GETGLOBALFIELD (55), PUSHGETGLOBALFIELD (56),
   - MAKEBLOCK (62), MAKEBLOCK1..MAKEBLOCK3 (63-65),
   - GETFIELD0..GETFIELD3 (67-70), GETFIELD (71),
   - SETFIELD0..SETFIELD3 (73-76), SETFIELD (77),
   - GETVECTITEM (80), SETVECTITEM (81),
   - OFFSETREF (128),
   - ATOM0 (58), ATOM (59), PUSHATOM0 (60), PUSHATOM (61). */
/* @requires mv points to a valid VM, instruction is the opcode at mv->codes[mv->pc]
   @assigns  mv->pc, mv->acc, mv->stack, mv->top, mv->tab_globals (depending on the opcode)
   @ensures  if instruction belongs to the "memory" category, executes it via the
             local switch and returns 1; otherwise returns 0 without touching mv */
int engine_eval_memory(vm *mv, int instruction);

#endif
