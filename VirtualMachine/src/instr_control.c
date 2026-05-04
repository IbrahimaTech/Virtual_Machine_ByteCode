#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "stack.h"
#include "primitives.h"
#include "instr_control.h"

/* @requires mv points to a valid VM
   @assigns  mv->running
   @ensures  sets mv->running = 0 to stop the main loop on next iteration */
void STOP(vm *mv){
    mv->running = 0; // execution of the machine stops
}

/* @requires mv points to a valid VM
   @assigns  mv->pc
   @ensures  increments mv->pc by 1 (no signal handling in this VM) */
void CHECK_SIGNALS(vm *mv){
    mv->pc += 1; // advance the program counter by default
}

/* @requires mv points to a valid VM
   @assigns  mv->pc
   @ensures  reads n from codes[pc+1], sets mv->pc += n + 1 */
void BRANCH(vm *mv){
    int n = mv->codes[mv->pc + 1];
    mv->pc += n + 1;
}

/* @requires mv points to a valid VM
   @assigns  mv->pc
   @ensures  if mv->acc != encode(0) then mv->pc += n + 1, else mv->pc += 2 */
void BRANCHIF(vm *mv){
    int n = mv->codes[mv->pc + 1];
    if(mv->acc != encode(0)) {// if mv->acc is not the encoding of false
         mv->pc += n + 1;
    }
    else{
        mv->pc += 2;
    }
}

/* @requires mv points to a valid VM
   @assigns  mv->pc
   @ensures  if mv->acc == encode(0) then mv->pc += n + 1, else mv->pc += 2 */
void BRANCHIFNOT(vm *mv){
    int n = mv->codes[mv->pc + 1];
    if( mv->acc == encode(0)){
        mv->pc += n + 1;
    }
    else{
        mv->pc += 2;
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  uses decoded acc as table index to look up jump offset, otherwise
             skips the entire jump table */
void SWITCH(vm *mv){
    int n = mv->codes[mv->pc + 1];
    long i = decode(mv->acc);
    if(i < n){
        int ci = mv->codes[mv->pc + 2 + (int)i]; // ensure homogeneous arithmetic
        // by casting i to int
        mv->pc += ci + 2;
    }
    else{
        mv->pc += n + 2; // if the configuration of the jump table does not match,
        // skip the whole table given in the spec
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded boolean
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with encoding of its negation */
void BOOLNOT(vm *mv){
    long b = decode(mv->acc);
    mv->acc = encode(1 - b); // replace the encoding with the encoding of its negation
    // 1 - b is 1 if b == 0 and 0 if b == 1
    mv->pc++;
}

/* @requires mv points to a valid VM, stack has at least one value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v; accumulator becomes encode(1) if mv->acc == v else encode(0) */
void EQ(vm *mv){
    value val = pop(mv);
    // mv->acc and val are not necessarily encoded integers,
    // so we cast both sides to value to be safe
    if((value)mv->acc == (value)val){
        mv->acc = encode(1);
        mv->pc += 1;
    }
    else{
        mv->acc = encode(0);
        mv->pc += 1;
    }
}

/* @requires mv points to a valid VM, stack has at least one value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v; accumulator becomes encode(0) if mv->acc == v else encode(1) */
void NEQ(vm *mv){
    value val = pop(mv);
    if((value)mv->acc == (value)val){
        mv->acc = encode(0);
        mv->pc += 1;
    }
    else{
        mv->acc = encode(1);
        mv->pc += 1;
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if n == m then mv->pc += c + 2, else mv->pc += 3 */
void BEQ(vm *mv){
    long n = decode(mv->acc);
    int m = mv->codes[mv->pc + 1]; // integer at the cell after the current opcode
    int c = mv->codes[mv->pc + 2]; // integer at the cell after that
    if(n == (long)m){
        mv->pc += c + 2;
    }
    else{
        mv->pc += 3;
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if n != m then mv->pc += c + 2, else mv->pc += 3 */
void BNEQ(vm *mv){
    long n = decode(mv->acc);
    int m = mv->codes[mv->pc + 1]; // integer at the cell after the current opcode
    int c = mv->codes[mv->pc + 2]; // integer at the cell after that
    if(n == (long)m){
        mv->pc += 3;
    }
    else {
         mv->pc += c + 2;
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if m < n then mv->pc += c + 2, else mv->pc += 3 */
void BLTINT(vm *mv){
     long n = decode(mv->acc);
     int m = mv->codes[mv->pc + 1]; // integer at the cell after the current opcode
    int c = mv->codes[mv->pc + 2]; // integer at the cell after that
    if((long)m < n){
        mv->pc += c + 2;
    }
    else {
        mv->pc += 3;
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if m <= n then mv->pc += c + 2, else mv->pc += 3 */
void BLEINT(vm *mv){
    long n = decode(mv->acc);
    int m = mv->codes[mv->pc + 1]; // integer at the cell after the current opcode
    int c = mv->codes[mv->pc + 2]; // integer at the cell after that
    if((long)m <= n){
        mv->pc += c + 2;
    }
    else {
        mv->pc += 3;
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if m > n then mv->pc += c + 2, else mv->pc += 3 */
void BGTINT(vm *mv){
    long n = decode(mv->acc);
    int m = mv->codes[mv->pc + 1]; // integer at the cell after the current opcode
    int c = mv->codes[mv->pc + 2]; // integer at the cell after that
    if((long)m > n){
        mv->pc += c + 2;
    }
    else {
        mv->pc += 3;
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if m >= n then mv->pc += c + 2, else mv->pc += 3 */
void BGEINT(vm *mv){
    long n = decode(mv->acc);
    int m = mv->codes[mv->pc + 1]; // integer at the cell after the current opcode
    int c = mv->codes[mv->pc + 2]; // integer at the cell after that
    if((long)m >= n){
        mv->pc += c + 2;
    }
    else {
        mv->pc += 3;
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if (unsigned)m < (unsigned)n then mv->pc += c + 2,
             else mv->pc += 3 */
void BULTINT(vm *mv){
    long n = decode(mv->acc); // decoded accumulator
    int m = mv->codes[mv->pc + 1]; // integer at the cell after the current opcode
    int c = mv->codes[mv->pc + 2]; // integer at the cell after that
    if((unsigned long)m < (unsigned long)n){ // unsigned comparison
        mv->pc += c + 2;
    }
    else {
        mv->pc += 3;
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->pc
   @ensures  reads m and c; if (unsigned)m >= (unsigned)n then mv->pc += c + 2,
             else mv->pc += 3 */
void BUGEINT(vm *mv){
    long n = decode(mv->acc); // decoded accumulator
    int m = mv->codes[mv->pc + 1]; // integer at the cell after the current opcode
    int c = mv->codes[mv->pc + 2]; // integer at the cell after that
    if((unsigned long)m >= (unsigned long)n){ // unsigned comparison
        mv->pc += c + 2;
    }
    else {
        mv->pc += 3;
    }
}

/* @requires mv points to a valid VM, codes[pc+1] is a primitive number
   @assigns  mv->acc, mv->pc
   @ensures  calls primitive with the accumulator and stores the result */
void C_CALL1(vm *mv){
    int n = mv->codes[mv->pc + 1];
    value arg[1]; // declare an array of size 1
    arg[0] = mv->acc; // value held in the accumulator
    // store the value returned by the primitive in the accumulator
    mv->acc = call_primitive(n, arg, 1);
    mv->pc += 2;
}

/* @requires mv points to a valid VM with at least 1 element on the stack
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops 1 value, calls primitive with (acc, popped) and stores result */
void C_CALL2(vm *mv){
    int n = mv->codes[mv->pc + 1];
    value v2 = pop(mv); // pop one value
    value v1 = mv->acc;
    value args[2]; // array of size 2
    args[0] = v1;
    args[1] = v2;
    mv->acc = call_primitive(n, args, 2);
    mv->pc += 2;
}

/* @requires mv points to a valid VM with at least 2 elements on the stack
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops 2 values, calls primitive with (acc, popped...) and stores result */
void C_CALL3(vm *mv){
    int n = mv->codes[mv->pc + 1];
    value v2 = pop(mv); // pop one value
    value v3 = pop(mv); // pop a second value
    value v1 = mv->acc;
    value args[3]; // array of size 3
    args[0] = v1;
    args[1] = v2;
    args[2] = v3;
    mv->acc = call_primitive(n,args,3);
    mv->pc += 2;
}

/* @requires mv points to a valid VM with at least 3 elements on the stack
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops 3 values, calls primitive with (acc, popped...) and stores result */
void C_CALL4(vm *mv){
    int n = mv->codes[mv->pc + 1];
    value v2 = pop(mv); // pop one value
    value v3 = pop(mv); // pop a second value
    value v4 = pop(mv); // pop a third value
    value v1 = mv->acc;
    value args[4]; // array of size 4
    args[0] = v1;
    args[1] = v2;
    args[2] = v3;
    args[3] = v4;
    mv->acc = call_primitive(n,args,4);
    mv->pc += 2;
}

/* @requires mv points to a valid VM with at least 4 elements on the stack
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops 4 values, calls primitive with (acc, popped...) and stores result */
void C_CALL5(vm *mv){
    int n = mv->codes[mv->pc + 1];
    value v2 = pop(mv); // pop one value
    value v3 = pop(mv); // pop a second value
    value v4 = pop(mv); // pop a third value
    value v5 = pop(mv); // pop a final value
    value v1 = mv->acc;
    value args[5]; // array of size 5
    args[0] = v1;
    args[1] = v2;
    args[2] = v3;
    args[3] = v4;
    args[4] = v5;
    mv->acc = call_primitive(n,args,5);
    mv->pc += 2;
}

/* @requires mv points to a valid VM, codes[pc+1]=p, codes[pc+2]=primitive number,
             stack has at least p-1 elements
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  builds p-sized array (acc + p-1 popped), calls primitive, frees array */
void C_CALLN(vm *mv){
    int p = mv->codes[mv->pc + 1];
    int n = mv->codes[mv->pc + 2];
    // allocate an array of values of size p
    value *args = (value*)malloc((size_t)p * sizeof(value));
    if(!args){
        perror("malloc");
        mv->pc += 1;
        exit(1);
    }
    args[0] = mv->acc ;
    for(int i = 1; i < p; i+=1){
        args[i] = pop(mv);
    }
    mv->acc = call_primitive(n, args,p);
    free(args);
    mv->pc += 3;
}
