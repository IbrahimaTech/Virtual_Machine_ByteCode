#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "stack.h"
#include "instr_base.h"

/* @requires mv points to a valid VM with at least 1 element on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 0 of the stack into the accumulator */
void ACC0(vm *mv){
    mv->acc = peek(mv, 0);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with at least 2 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 1 of the stack into the accumulator */
void ACC1(vm *mv){
    mv->acc = peek(mv, 1);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with at least 3 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 2 of the stack into the accumulator */
void ACC2(vm *mv){
    mv->acc = peek(mv, 2);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with at least 4 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 3 of the stack into the accumulator */
void ACC3(vm *mv){
    mv->acc = peek(mv, 3);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with at least 5 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 4 of the stack into the accumulator */
void ACC4(vm *mv){
    mv->acc = peek(mv, 4);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with at least 6 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 5 of the stack into the accumulator */
void ACC5(vm *mv){
    mv->acc = peek(mv, 5);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with at least 7 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 6 of the stack into the accumulator */
void ACC6(vm *mv){
    mv->acc = peek(mv, 6);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with at least 8 elements on the stack
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth 7 of the stack into the accumulator */
void ACC7(vm *mv){
    mv->acc = peek(mv, 7);
    mv->pc +=1;
}

/* @requires mv points to a valid VM, mv->codes[mv->pc + 1] is a valid stack depth n
   @assigns  mv->acc, mv->pc
   @ensures  loads the value at depth n into the accumulator, mv->pc += 2 */
void ACC(vm *mv){
    int n = mv->codes[mv->pc + 1];
    mv->acc = peek(mv, n);
    mv->pc += 2;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->pc
   @ensures  pushes the accumulator onto the stack */
void PUSH(vm *mv){
    push(mv, mv->acc); // push the content of the accumulator
    mv->pc +=1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 0 into the accumulator */
void PUSHACC0(vm *mv){
    push(mv, mv->acc);
    value tmp = peek(mv,0); // element at depth 0
    mv->acc = tmp;
    mv->pc +=1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 1 into the accumulator */
void PUSHACC1(vm *mv){
    push(mv, mv->acc);
    mv->acc = peek(mv, 1);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 2 into the accumulator */
void PUSHACC2(vm *mv){
    push(mv, mv->acc);
    mv->acc = peek(mv,2);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 3 into the accumulator */
void PUSHACC3(vm *mv){
    push(mv, mv->acc);
    mv->acc = peek(mv, 3);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 4 into the accumulator */
void PUSHACC4(vm *mv){
    push(mv, mv->acc);
    mv->acc = peek(mv, 4);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 5 into the accumulator */
void PUSHACC5(vm *mv){
    push(mv, mv->acc);
    mv->acc = peek(mv, 5);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 6 into the accumulator */
void PUSHACC6(vm *mv){
   push(mv, mv->acc);
    mv->acc = peek(mv, 6);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth 7 into the accumulator */
void PUSHACC7(vm *mv){
    push(mv, mv->acc);
    mv->acc = peek(mv, 7);
    mv->pc +=1;
}

/* @requires mv points to a valid VM with stack not full,
             mv->codes[mv->pc + 1] is a valid stack depth n
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads new stack depth n into the accumulator */
void PUSHACC(vm *mv){
    int n = mv->codes[mv->pc + 1];
    push(mv, mv->acc);
    mv->acc = peek(mv, n);
    mv->pc +=2;
}

/* @requires mv points to a valid VM, n elements are available on the stack
   @assigns  mv->stack, mv->top, mv->pc
   @ensures  pops n elements from the stack, mv->pc += 2 */
void POP(vm *mv){
    int n = mv->codes[mv->pc + 1];
    for(int i = 0; i < n; i++){
        pop(mv);
    }
    mv->pc += 2;
}

/* @requires mv points to a valid VM, mv->codes[mv->pc + 1] is a valid stack depth
   @assigns  mv->stack, mv->acc, mv->pc
   @ensures  replaces the value at depth n with the accumulator, sets the
             accumulator to encode(0), mv->pc += 2 */
void ASSIGN(vm *mv){
    int n = mv->codes[mv->pc + 1];
    if(n > mv->top){ // handle the case where we are out of stack bounds
        fprintf(stderr, "ASSIGN: out of stack bounds\n");
        exit(1);
    }
    mv->stack[mv->top - n] = mv->acc;
    mv->acc = encode(0);
    mv->pc += 2;
}
