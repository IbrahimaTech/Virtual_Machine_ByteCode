#ifndef STACK_H
#define STACK_H

#include "types.h"

/* Initialize the stack */
/* @requires mv points to a valid VM
   @assigns  mv->stack, mv->top, mv->max_stack_size
   @ensures  mv->stack is allocated and empty (mv->top == -1) */
void init_stack(vm *mv);

/* Push a value onto the stack */
/* @requires mv points to a valid VM
   @assigns  mv->stack, mv->top
   @ensures  pushes v onto the stack, exits with code 1 on stack overflow */
void push(vm *mv, value v);

/* Pop the top of the stack */
/* @requires mv points to a valid VM with at least one element on the stack
   @assigns  mv->stack, mv->top
   @ensures  pops the top element and returns it, exits with code 1 on underflow */
value pop(vm *mv);

/* Read the value at a given depth in the stack */
/* @requires mv points to a valid VM, depth <= mv->top
   @assigns  nothing
   @ensures  returns the element at the given depth without modifying the stack */
value peek(vm *mv, int depth);

#endif
