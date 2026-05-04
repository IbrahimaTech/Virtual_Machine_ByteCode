#ifndef INSTR_BASE_H
#define INSTR_BASE_H

#include "types.h"

/* ACC0
   @requires mv points to a valid VM with at least 1 element on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 0 of the stack into the accumulator,
             increments mv->pc by 1 */
void ACC0(vm *mv);

/* ACC1
   @requires mv points to a valid VM with at least 2 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 1 of the stack into the accumulator,
             increments mv->pc by 1 */
void ACC1(vm *mv);

/* ACC2
   @requires mv points to a valid VM with at least 3 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 2 of the stack into the accumulator,
             increments mv->pc by 1 */
void ACC2(vm *mv);

/* ACC3
   @requires mv points to a valid VM with at least 4 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 3 of the stack into the accumulator,
             increments mv->pc by 1 */
void ACC3(vm *mv);

/* ACC4
   @requires mv points to a valid VM with at least 5 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 4 of the stack into the accumulator,
             increments mv->pc by 1 */
void ACC4(vm *mv);

/* ACC5
   @requires mv points to a valid VM with at least 6 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 5 of the stack into the accumulator,
             increments mv->pc by 1 */
void ACC5(vm *mv);

/* ACC6
   @requires mv points to a valid VM with at least 7 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 6 of the stack into the accumulator,
             increments mv->pc by 1 */
void ACC6(vm *mv);

/* ACC7
   @requires mv points to a valid VM with at least 8 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 7 of the stack into the accumulator,
             increments mv->pc by 1 */
void ACC7(vm *mv);

/* ACC
   @requires mv points to a valid VM, mv->codes[mv->pc + 1] is a valid stack depth n
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth n into the accumulator, mv->pc += 2 */
void ACC(vm *mv);

/* PUSH
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->pc
   @ensures  pushes the accumulator onto the stack, increments mv->pc by 1 */
void PUSH(vm *mv);

/* PUSHACC0
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 0 into the
             accumulator, increments mv->pc by 1 */
void PUSHACC0(vm *mv);

/* PUSHACC1
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 1 into the
             accumulator, increments mv->pc by 1 */
void PUSHACC1(vm *mv);

/* PUSHACC2
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 2 into the
             accumulator, increments mv->pc by 1 */
void PUSHACC2(vm *mv);

/* PUSHACC3
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 3 into the
             accumulator, increments mv->pc by 1 */
void PUSHACC3(vm *mv);

/* PUSHACC4
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 4 into the
             accumulator, increments mv->pc by 1 */
void PUSHACC4(vm *mv);

/* PUSHACC5
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 5 into the
             accumulator, increments mv->pc by 1 */
void PUSHACC5(vm *mv);

/* PUSHACC6
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 6 into the
             accumulator, increments mv->pc by 1 */
void PUSHACC6(vm *mv);

/* PUSHACC7
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 7 into the
             accumulator, increments mv->pc by 1 */
void PUSHACC7(vm *mv);

/* PUSHACC
   @requires mv points to a valid VM with stack not full,
             mv->codes[mv->pc + 1] is a valid stack depth n
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth n into the
             accumulator, mv->pc += 2 */
void PUSHACC(vm *mv);

/* POP
   @requires mv points to a valid VM, mv->codes[mv->pc + 1] is a non-negative
             integer n with at least n elements on the stack
   @assigns  mv->stack, mv->top, mv->pc
   @ensures  pops n elements from the stack, mv->pc += 2 */
void POP(vm *mv);

/* ASSIGN
   @requires mv points to a valid VM, mv->codes[mv->pc + 1] is a valid stack depth
   @assigns  mv->stack, mv->acc, mv->pc
   @ensures  replaces the value at depth n with the accumulator, sets the
             accumulator to encode(0), mv->pc += 2 */
void ASSIGN(vm *mv);

#endif
