#ifndef INSTR_CONTROL_H
#define INSTR_CONTROL_H

#include "types.h"

/* STOP
   @requires mv points to a valid VM
   @assigns  mv->running
   @ensures  sets mv->running = 0 to stop the main loop on next iteration */
void STOP(vm *mv);

/* CHECK_SIGNALS
   @requires mv points to a valid VM
   @assigns  mv->pc
   @ensures  increments mv->pc by 1 (no signal handling in this VM) */
void CHECK_SIGNALS(vm *mv);

/* BRANCH
   @requires mv points to a valid VM
   @assigns  mv->pc
   @ensures  reads n from mv->codes[mv->pc + 1], sets mv->pc += n + 1 */
void BRANCH(vm *mv);

/* BRANCHIF
   @requires mv points to a valid VM
   @assigns  mv->pc
   @ensures  reads n from mv->codes[mv->pc + 1]; if mv->acc != encode(0)
             then mv->pc += n + 1, else mv->pc += 2 */
void BRANCHIF(vm *mv);

/* BRANCHIFNOT
   @requires mv points to a valid VM
   @assigns  mv->pc
   @ensures  reads n from mv->codes[mv->pc + 1]; if mv->acc == encode(0)
             then mv->pc += n + 1, else mv->pc += 2 */
void BRANCHIFNOT(vm *mv);

/* SWITCH
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads n from mv->codes[mv->pc + 1] and uses the decoded
             accumulator i to look up ci in the jump table at
             mv->codes[mv->pc + 2 + i]; jumps accordingly or skips the table */
void SWITCH(vm *mv);

/* BOOLNOT
   @requires mv points to a valid VM, accumulator holds an encoded boolean
   @assigns  mv->acc, mv->pc
   @ensures  replaces the accumulator with the encoding of its negation
             (encode(0) <-> encode(1)), increments mv->pc by 1 */
void BOOLNOT(vm *mv);

/* EQ
   @requires mv points to a valid VM, stack has at least one value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops a value v, accumulator becomes encode(1) if mv->acc == v
             (raw value comparison), else encode(0); increments mv->pc by 1 */
void EQ(vm *mv);

/* NEQ
   @requires mv points to a valid VM, stack has at least one value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops a value v, accumulator becomes encode(0) if mv->acc == v
             else encode(1); increments mv->pc by 1 */
void NEQ(vm *mv);

/* BEQ
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m at mv->codes[mv->pc + 1] and c at mv->codes[mv->pc + 2];
             if n == m then mv->pc += c + 2, else mv->pc += 3 */
void BEQ(vm *mv);

/* BNEQ
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if n != m then mv->pc += c + 2, else mv->pc += 3 */
void BNEQ(vm *mv);

/* BLTINT
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if m < n then mv->pc += c + 2, else mv->pc += 3 */
void BLTINT(vm *mv);

/* BLEINT
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if m <= n then mv->pc += c + 2, else mv->pc += 3 */
void BLEINT(vm *mv);

/* BGTINT
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if m > n then mv->pc += c + 2, else mv->pc += 3 */
void BGTINT(vm *mv);

/* BGEINT
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if m >= n then mv->pc += c + 2, else mv->pc += 3 */
void BGEINT(vm *mv);

/* BULTINT
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if (unsigned)m < (unsigned)n then mv->pc += c + 2,
             else mv->pc += 3 */
void BULTINT(vm *mv);

/* BUGEINT
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if (unsigned)m >= (unsigned)n then mv->pc += c + 2,
             else mv->pc += 3 */
void BUGEINT(vm *mv);

/* C_CALL1
   @requires mv points to a valid VM, mv->codes[mv->pc + 1] is a primitive number
   @assigns  mv->acc, mv->pc
   @ensures  calls primitive with the accumulator as sole argument and stores
             the result in the accumulator; mv->pc += 2 */
void C_CALL1(vm *mv);

/* C_CALL2
   @requires mv points to a valid VM with at least 1 element on the stack
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops 1 value, calls primitive with (accumulator, popped) and stores
             the result in the accumulator; mv->pc += 2 */
void C_CALL2(vm *mv);

/* C_CALL3
   @requires mv points to a valid VM with at least 2 elements on the stack
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops 2 values, calls primitive with (accumulator + 2 popped) and
             stores the result in the accumulator; mv->pc += 2 */
void C_CALL3(vm *mv);

/* C_CALL4
   @requires mv points to a valid VM with at least 3 elements on the stack
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops 3 values, calls primitive with (accumulator + 3 popped) and
             stores the result in the accumulator; mv->pc += 2 */
void C_CALL4(vm *mv);

/* C_CALL5
   @requires mv points to a valid VM with at least 4 elements on the stack
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops 4 values, calls primitive with (accumulator + 4 popped) and
             stores the result in the accumulator; mv->pc += 2 */
void C_CALL5(vm *mv);

/* C_CALLN
   @requires mv points to a valid VM, mv->codes[mv->pc + 1] is the count p,
             mv->codes[mv->pc + 2] is the primitive number,
             stack has at least p - 1 elements
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  builds a p-sized argument array (accumulator + p-1 popped values),
             calls the primitive, stores the result in the accumulator,
             frees the temporary array; mv->pc += 3 */
void C_CALLN(vm *mv);

#endif
