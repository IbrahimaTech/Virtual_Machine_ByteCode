#ifndef ENGINE_H
#define ENGINE_H

#include "types.h"

/* Main entry point of the virtual machine */
/* @requires mv points to a valid VM whose codes array has been populated
   @assigns  mv->pc, mv->acc, mv->running, mv->stack, mv->tab_globals
   @ensures  initializes the VM state, runs the main fetch-evaluate loop by
             dispatching each opcode to the appropriate evaluator module
             (base / arithmetic / control / memory) until STOP, an unknown
             opcode, or pc out of bounds; returns the final accumulator value */
value virtual_machine(vm *mv);

#endif
