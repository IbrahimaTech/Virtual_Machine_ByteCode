#ifndef INSTR_MEMORY_H
#define INSTR_MEMORY_H

#include "types.h"

/* GETGLOBAL
   @requires mv points to a valid VM, mv->codes[mv->pc + 1] is a valid global index
   @assigns  mv->acc, mv->pc
   @ensures  loads mv->tab_globals[n] into the accumulator; mv->pc += 2.
             Exits with code 1 if n is out of range. */
void GETGLOBAL(vm *mv);

/* PUSHGETGLOBAL
   @requires mv points to a valid VM with stack not full,
             mv->codes[mv->pc + 1] is a valid global index
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads mv->tab_globals[n] into the
             accumulator; mv->pc += 2 */
void PUSHGETGLOBAL(vm *mv);

/* SETGLOBAL
   @requires mv points to a valid VM, mv->codes[mv->pc + 1] is a valid global index
   @assigns  mv->tab_globals, mv->acc, mv->pc
   @ensures  stores the accumulator into mv->tab_globals[n], sets the accumulator
             to encode(0); mv->pc += 2 */
void SETGLOBAL(vm *mv);

/* MAKEBLOCK
   @requires mv points to a valid VM, mv->codes[mv->pc + 1] is the block size
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  allocates a block of size n, stores accumulator at index 0 and the
             remaining slots from popped stack values; accumulator becomes the
             block address; mv->pc += 3 */
void MAKEBLOCK(vm *mv);

/* MAKEBLOCK1
   @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  allocates a block of size 1 holding the accumulator, accumulator
             becomes the block address; mv->pc += 2 */
void MAKEBLOCK1(vm *mv);

/* MAKEBLOCK2
   @requires mv points to a valid VM with at least 1 stack element
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  allocates a block of size 2 (accumulator at 0, popped at 1),
             accumulator becomes the block address; mv->pc += 2 */
void MAKEBLOCK2(vm *mv);

/* MAKEBLOCK3
   @requires mv points to a valid VM with at least 2 stack elements
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  allocates a block of size 3 (accumulator at 0, popped at 1 and 2),
             accumulator becomes the block address; mv->pc += 2 */
void MAKEBLOCK3(vm *mv);

/* GETFIELD0
   @requires mv points to a valid VM, accumulator points to a valid block
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with block[0]; increments mv->pc by 1 */
void GETFIELD0(vm *mv);

/* GETFIELD1
   @requires mv points to a valid VM, accumulator points to a valid block
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with block[1]; increments mv->pc by 1 */
void GETFIELD1(vm *mv);

/* GETFIELD2
   @requires mv points to a valid VM, accumulator points to a valid block
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with block[2]; increments mv->pc by 1 */
void GETFIELD2(vm *mv);

/* GETFIELD3
   @requires mv points to a valid VM, accumulator points to a valid block
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with block[3]; increments mv->pc by 1 */
void GETFIELD3(vm *mv);

/* GETFIELD
   @requires mv points to a valid VM, accumulator points to a valid block,
             mv->codes[mv->pc + 1] is a valid field index n
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with block[n]; mv->pc += 2 */
void GETFIELD(vm *mv);

/* SETFIELD0
   @requires mv points to a valid VM, accumulator points to a valid block,
             stack has at least one value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v, stores v in block[0], sets accumulator to encode(0);
             increments mv->pc by 1 */
void SETFIELD0(vm *mv);

/* SETFIELD1
   @requires mv points to a valid VM, accumulator points to a valid block,
             stack has at least one value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v, stores v in block[1], sets accumulator to encode(0);
             increments mv->pc by 1 */
void SETFIELD1(vm *mv);

/* SETFIELD2
   @requires mv points to a valid VM, accumulator points to a valid block,
             stack has at least one value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v, stores v in block[2], sets accumulator to encode(0);
             increments mv->pc by 1 */
void SETFIELD2(vm *mv);

/* SETFIELD3
   @requires mv points to a valid VM, accumulator points to a valid block,
             stack has at least one value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v, stores v in block[3], sets accumulator to encode(0);
             increments mv->pc by 1 */
void SETFIELD3(vm *mv);

/* SETFIELD
   @requires mv points to a valid VM, accumulator points to a valid block,
             mv->codes[mv->pc + 1] is a valid field index n,
             stack has at least one value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v, stores v in block[n], sets accumulator to encode(0);
             mv->pc += 2 */
void SETFIELD(vm *mv);

/* GETVECTITEM
   @requires mv points to a valid VM, accumulator points to a valid block,
             stack top is an encoded index
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops n (decoded), replaces accumulator with block[n];
             increments mv->pc by 1 */
void GETVECTITEM(vm *mv);

/* SETVECTITEM
   @requires mv points to a valid VM, accumulator points to a valid block,
             stack has at least 2 values (top is an encoded index, then v)
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops n (decoded) and v, stores v at block[n], sets accumulator
             to encode(0); increments mv->pc by 1 */
void SETVECTITEM(vm *mv);

/* GETGLOBALFIELD
   @requires mv points to a valid VM, mv->codes[mv->pc + 1] is a valid global
             index n, mv->tab_globals[n] points to a valid block,
             mv->codes[mv->pc + 2] is a valid field index p
   @assigns  mv->acc, mv->pc
   @ensures  loads mv->tab_globals[n][p] into the accumulator; mv->pc += 3 */
void GETGLOBALFIELD(vm *mv);

/* PUSHGETGLOBALFIELD
   @requires mv points to a valid VM with stack not full,
             mv->codes[mv->pc + 1] is a valid global index n,
             mv->tab_globals[n] points to a valid block,
             mv->codes[mv->pc + 2] is a valid field index p
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads mv->tab_globals[n][p] into the
             accumulator; mv->pc += 3 */
void PUSHGETGLOBALFIELD(vm *mv);

/* OFFSETREF
   @requires mv points to a valid VM, accumulator points to a valid block whose
             field 0 holds an encoded integer
   @assigns  mv->acc, mv->pc
   @ensures  replaces block[0] with encode(m + n) (where n is at codes[pc+1]),
             sets accumulator to encode(0); mv->pc += 2 */
void OFFSETREF(vm *mv);

/* ATOM0
   @requires mv points to a valid VM whose tab_atoms field is initialized
   @assigns  mv->acc, mv->pc
   @ensures  loads (value)mv->tab_atoms[0] into the accumulator;
             increments mv->pc by 1 */
void ATOM0(vm *mv);

/* ATOM
   @requires mv points to a valid VM whose tab_atoms field is initialized,
             mv->codes[mv->pc + 1] is a valid atom index n in [0, 256)
   @assigns  mv->acc, mv->pc
   @ensures  loads (value)mv->tab_atoms[n] into the accumulator; mv->pc += 2 */
void ATOM(vm *mv);

/* PUSHATOM0
   @requires mv points to a valid VM with stack not full,
             mv->tab_atoms is initialized
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads (value)mv->tab_atoms[0] into the
             accumulator; increments mv->pc by 1 */
void PUSHATOM0(vm *mv);

/* PUSHATOM
   @requires mv points to a valid VM with stack not full,
             mv->codes[mv->pc + 1] is a valid atom index n,
             mv->tab_atoms is initialized
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads (value)mv->tab_atoms[n] into the
             accumulator; mv->pc += 2 */
void PUSHATOM(vm *mv);

#endif
