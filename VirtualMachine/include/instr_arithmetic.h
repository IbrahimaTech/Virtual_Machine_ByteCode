#ifndef INSTR_ARITHMETIC_H
#define INSTR_ARITHMETIC_H

#include "types.h"

/* CONST0
   @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  loads encode(0) into the accumulator, increments mv->pc by 1 */
void CONST0(vm *mv);

/* CONST1
   @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  loads encode(1) into the accumulator, increments mv->pc by 1 */
void CONST1(vm *mv);

/* CONST2
   @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  loads encode(2) into the accumulator, increments mv->pc by 1 */
void CONST2(vm *mv);

/* CONST3
   @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  loads encode(3) into the accumulator, increments mv->pc by 1 */
void CONST3(vm *mv);

/* CONSTINT
   @requires mv points to a valid VM, mv->codes[mv->pc + 1] is an integer n
   @assigns  mv->acc, mv->pc
   @ensures  loads encode(n) into the accumulator, mv->pc += 2 */
void CONSTINT(vm *mv);

/* PUSHCONST0
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads encode(0) into the accumulator,
             increments mv->pc by 1 */
void PUSHCONST0(vm *mv);

/* PUSHCONST1
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads encode(1) into the accumulator,
             increments mv->pc by 1 */
void PUSHCONST1(vm *mv);

/* PUSHCONST2
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads encode(2) into the accumulator,
             increments mv->pc by 1 */
void PUSHCONST2(vm *mv);

/* PUSHCONST3
   @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads encode(3) into the accumulator,
             increments mv->pc by 1 */
void PUSHCONST3(vm *mv);

/* PUSHCONSTINT
   @requires mv points to a valid VM with stack not full,
             mv->codes[mv->pc + 1] is an integer n
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads encode(n) into the accumulator,
             mv->pc += 2 */
void PUSHCONSTINT(vm *mv);

/* NEGINT
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->acc, mv->pc
   @ensures  replaces the accumulator with encode(-n), increments mv->pc by 1 */
void NEGINT(vm *mv);

/* ADDINT
   @requires mv points to a valid VM, accumulator holds an encoded integer,
             stack top holds an encoded integer
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n + m),
             increments mv->pc by 1 */
void ADDINT(vm *mv);

/* SUBINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n - m),
             increments mv->pc by 1 */
void SUBINT(vm *mv);

/* MULINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n * m),
             increments mv->pc by 1 */
void MULINT(vm *mv);

/* DIVINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m. If m == 0, prints fatal error and exits with code 2;
             otherwise replaces the accumulator with encode(n / m),
             increments mv->pc by 1 */
void DIVINT(vm *mv);

/* MODINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m. If m == 0, prints fatal error and exits with code 2;
             otherwise replaces the accumulator with encode(n % m),
             increments mv->pc by 1 */
void MODINT(vm *mv);

/* ANDINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n & m),
             increments mv->pc by 1 */
void ANDINT(vm *mv);

/* ORINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n | m),
             increments mv->pc by 1 */
void ORINT(vm *mv);

/* XORINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n ^ m),
             increments mv->pc by 1 */
void XORINT(vm *mv);

/* LSLINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n << m),
             increments mv->pc by 1 */
void LSLINT(vm *mv);

/* LSRINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with the logical right shift of
             n by m bits (sign not preserved), increments mv->pc by 1 */
void LSRINT(vm *mv);

/* ASRINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with the arithmetic right shift of
             n by m bits (sign preserved), increments mv->pc by 1 */
void ASRINT(vm *mv);

/* LTINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if n < m else encode(0),
             increments mv->pc by 1 */
void LTINT(vm *mv);

/* LEINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if n <= m else encode(0),
             increments mv->pc by 1 */
void LEINT(vm *mv);

/* GTINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if n > m else encode(0),
             increments mv->pc by 1 */
void GTINT(vm *mv);

/* GEINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if n >= m else encode(0),
             increments mv->pc by 1 */
void GEINT(vm *mv);

/* ULTINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if (unsigned)n < (unsigned)m
             else encode(0), increments mv->pc by 1 */
void ULTINT(vm *mv);

/* UGEINT
   @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if (unsigned)n >= (unsigned)m
             else encode(0), increments mv->pc by 1 */
void UGEINT(vm *mv);

/* OFFSETINT
   @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->acc, mv->pc
   @ensures  replaces the accumulator with encode(n + m), where m is read from
             mv->codes[mv->pc + 1], mv->pc += 2 */
void OFFSETINT(vm *mv);

/* ISINT
   @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  if accumulator value is odd (i.e. an encoded integer), accumulator
             becomes encode(1), else encode(0); increments mv->pc by 1 */
void ISINT(vm *mv);

#endif
