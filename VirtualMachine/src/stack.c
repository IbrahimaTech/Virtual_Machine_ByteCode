#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* @requires mv points to a valid VM
   @assigns  mv->stack, mv->top, mv->max_stack_size
   @ensures  mv->stack is allocated and empty (mv->top == -1) */
void init_stack(vm *mv){
    mv->max_stack_size = 1000;
    mv->stack = malloc(mv->max_stack_size * sizeof(value)); // allocate an array of size 1000
    mv->top = -1;
}

/* @requires mv points to a valid VM
   @assigns  mv->stack, mv->top
   @ensures  pushes v onto the stack, exits with code 1 on stack overflow */
void push(vm *mv ,value v){
    // check whether the stack is full
    if(mv->top >= mv->max_stack_size - 1) {
        fprintf(stderr, "Error: stack full\n");
        exit(1);
    }

    int top = mv->top ; // index of the top
    mv->stack[top + 1] = v; // push the value
    mv->top++; // increment because we just added an element
}

/* @requires mv points to a valid VM with at least one element on the stack
   @assigns  mv->stack, mv->top
   @ensures  pops the top element and returns it, exits with code 1 on underflow */
value pop(vm *mv){
    int top = mv->top; // index of the top
    // check whether the stack is empty
    if( top < 0){
        fprintf(stderr,"Error: stack empty\n");
        exit(1);
    }
    // otherwise
    value p = mv->stack[mv->top]; // element at the top
    mv->top--; // pop
    return p;
}

/* @requires mv points to a valid VM, depth <= mv->top
   @assigns  nothing
   @ensures  returns the element at the given depth without modifying the stack */
value peek(vm *mv, int depth){
    // On a depth error, abort the function
    if(depth > mv->top) {
        fprintf(stderr, "Error: out of stack bounds\n");
        exit(1);
    }
    return mv->stack[mv->top - depth];
}
