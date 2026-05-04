#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "stack.h"
#include "instr_memory.h"

/* @requires mv points to a valid VM, codes[pc+1] is a valid global index
   @assigns  mv->acc, mv->pc
   @ensures  loads mv->tab_globals[n] into the accumulator */
void GETGLOBAL(vm *mv){
    int n = mv->codes[mv->pc + 1];
    if(n < mv->nb_globals && n >= 0){
        mv->acc = mv->tab_globals[n]; // store the value at index n of the
        // globals array into the accumulator
    }
    else { // handle errors
        fprintf(stderr, "GETGLOBAL: invalid index\n");
        exit(1);
    }
    mv->pc += 2;
}

/* @requires mv points to a valid VM with stack not full, codes[pc+1] is valid
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes acc, then loads mv->tab_globals[n] into the accumulator */
void PUSHGETGLOBAL(vm *mv){
    int n = mv->codes[mv->pc + 1];
    push(mv,mv->acc); // push the content of the accumulator
    if(n < mv->nb_globals && n >= 0){
        mv->acc = mv->tab_globals[n]; // store the value at index n of the
        // globals array into the accumulator
    }
    else {
        fprintf(stderr, "PUSHGETGLOBAL: invalid index\n");
        exit(1);
    }
    mv->pc += 2;
}

/* @requires mv points to a valid VM, codes[pc+1] is a valid global index
   @assigns  mv->tab_globals, mv->acc, mv->pc
   @ensures  stores accumulator into mv->tab_globals[n], sets acc to encode(0) */
void SETGLOBAL(vm *mv){
    int n = mv->codes[mv->pc + 1];
    if(n < mv->nb_globals && n >= 0){
        mv->tab_globals[n] = mv->acc;
    }
    else {
        fprintf(stderr, "SETGLOBAL: invalid index\n");
        exit(1);
    }
    mv->acc = encode(0); // value cast
    mv->pc += 2;
}

/* @requires mv points to a valid VM, codes[pc+1] is the block size n
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  allocates a block of size n holding (acc, popped...), accumulator
             becomes the block address */
void MAKEBLOCK(vm *mv){
    int n = mv->codes[mv->pc + 1];
    if(n <= 0){
        n = 1; // ensure we always have an array of size at least 1
    }
    // if the number of elements on the stack (mv->top + 1) is strictly less
    // than the number of elements we want to pop
    if (mv->top < n - 2) {
        fprintf(stderr, "Error: not enough elements for MAKEBLOCK\n");
        exit(1);
    }
    // allocate an array of n values
    value *block = (value*)malloc((size_t)n * sizeof(value));
    if(!block){
        perror("malloc MAKEBLOCK");
        exit(1);
    }
    block[0] = mv->acc;
    for(int i = 1; i < n; i++){
        block[i] = pop(mv);
    }
    mv->acc = (value)block; // store the block address in the accumulator
    mv->pc += 3;
}

/* @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  allocates a block of size 1 holding the accumulator */
void MAKEBLOCK1(vm *mv){
    value *block = (value*)malloc(sizeof(value));
    if(!block) {
         perror("malloc MAKEBLOCK1");
         exit(1);
     }
    block[0] = mv->acc;
    mv->acc = (value)block;
    mv->pc += 2;
}

/* @requires mv points to a valid VM with at least 1 stack element
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  allocates a block of size 2 holding (acc, popped) */
void MAKEBLOCK2(vm *mv){
    value *block = (value*)malloc(2 * sizeof(value));
    if(!block) { perror("malloc MAKEBLOCK2");
         exit(1);
     }
    block[0] = mv->acc;
    block[1] = pop(mv);
    mv->acc = (value)block; // cast pointer to value
    mv->pc += 2;
}

/* @requires mv points to a valid VM with at least 2 stack elements
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  allocates a block of size 3 holding (acc, popped, popped) */
void MAKEBLOCK3(vm *mv){
    value *block = (value*)malloc(3 * sizeof(value));
    if(!block) { perror("malloc MAKEBLOCK3");
         exit(1);
     }
    block[0] = mv->acc;
    block[1] = pop(mv);
    block[2] = pop(mv);
    mv->acc = (value)block; // cast pointer to value
    mv->pc += 2;
}

/* @requires mv points to a valid VM, accumulator points to a valid block
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with block[0] */
void GETFIELD0(vm *mv){
    value *tab = (value*)mv->acc;
    if(!tab) {
        fprintf(stderr, "GETFIELD0: accumulator is null\n");
        exit(1);
    }
    mv->acc = tab[0];
    mv->pc++;
}

/* @requires mv points to a valid VM, accumulator points to a valid block
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with block[1] */
void GETFIELD1(vm *mv){
    value *tab = (value*)mv->acc;
    if(!tab) {
        fprintf(stderr, "GETFIELD1: accumulator is null\n");
        exit(1);
    }
    mv->acc = tab[1];
    mv->pc++;
}

/* @requires mv points to a valid VM, accumulator points to a valid block
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with block[2] */
void GETFIELD2(vm *mv){
    value *tab = (value*)mv->acc;
    if(!tab) {
        fprintf(stderr, "GETFIELD2: accumulator is null\n");
        exit(1);
    }
    mv->acc = tab[2];
    mv->pc++;
}

/* @requires mv points to a valid VM, accumulator points to a valid block
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with block[3] */
void GETFIELD3(vm *mv){
    value *tab = (value*)mv->acc;
    if(!tab) {
        fprintf(stderr, "GETFIELD3: accumulator is null\n");
        exit(1);
    }
    mv->acc = tab[3];
    mv->pc++;
}

/* @requires mv points to a valid VM, accumulator points to a valid block,
             codes[pc+1] is a valid field index
   @assigns  mv->acc, mv->pc
   @ensures  replaces accumulator with block[n] */
void GETFIELD(vm *mv){
    int n = mv->codes[mv->pc + 1];
    value *tab = (value*)mv->acc;
    if(!tab) {
         fprintf(stderr, "GETFIELD: accumulator is null\n");
         exit(1);
     }
    mv->acc = tab[n];
    mv->pc += 2;
}

/* @requires mv points to a valid VM, acc points to a valid block, stack has at least 1 value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v, stores v in block[0], sets acc to encode(0) */
void SETFIELD0(vm *mv){
    value *tab = (value*)mv->acc;
    if(!tab) {
         fprintf(stderr, "SETFIELD0: accumulator is null\n");
         exit(1);
     }
    tab[0] = pop(mv);
    mv->acc = encode(0);
    mv->pc++;
}

/* @requires mv points to a valid VM, acc points to a valid block, stack has at least 1 value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v, stores v in block[1], sets acc to encode(0) */
void SETFIELD1(vm *mv){
    value *tab = (value*)mv->acc;
    if(!tab) {
         fprintf(stderr, "SETFIELD1: accumulator is null\n");
         exit(1);
     }
    tab[1] = pop(mv);
    mv->acc = encode(0);
    mv->pc++;
}

/* @requires mv points to a valid VM, acc points to a valid block, stack has at least 1 value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v, stores v in block[2], sets acc to encode(0) */
void SETFIELD2(vm *mv){
    value *tab = (value*)mv->acc;
    if(!tab) {
         fprintf(stderr, "SETFIELD2: accumulator is null\n");
         exit(1);
     }
    tab[2] = pop(mv);
    mv->acc = encode(0);
    mv->pc++;
}

/* @requires mv points to a valid VM, acc points to a valid block, stack has at least 1 value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v, stores v in block[3], sets acc to encode(0) */
void SETFIELD3(vm *mv){
    value *tab = (value*)mv->acc;
    if(!tab) {
         fprintf(stderr, "SETFIELD3: accumulator is null\n");
         exit(1);
     }
    tab[3] = pop(mv);
    mv->acc = encode(0);
    mv->pc++;
}

/* @requires mv points to a valid VM, acc points to a valid block,
             codes[pc+1] is a valid field index, stack has at least 1 value
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops v, stores v in block[n], sets acc to encode(0) */
void SETFIELD(vm *mv){
    int n = mv->codes[mv->pc + 1];
    value *tab = (value*)mv->acc;
    if(!tab) {
         fprintf(stderr, "SETFIELD: accumulator is null\n");
         exit(1);
     }
    tab[n] = pop(mv);
    mv->acc = encode(0);
    mv->pc += 2;
}

/* @requires mv points to a valid VM, acc points to a valid block,
             stack top is an encoded index
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops n (decoded), replaces acc with block[n] */
void GETVECTITEM(vm *mv){
    long n = decode(pop(mv));
    value *tab = (value*)mv->acc;
    if(!tab) {
         fprintf(stderr, "GETVECTITEM: accumulator is null\n");
         exit(1);
     }
    mv->acc = tab[(int)n];
    mv->pc++;
}

/* @requires mv points to a valid VM, acc points to a valid block,
             stack has at least 2 elements
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops n (decoded) and v, stores v at block[n], sets acc to encode(0) */
void SETVECTITEM(vm *mv){
    long n = decode(pop(mv));
    value v = pop(mv);
    value *tab = (value*)mv->acc;
    if(!tab) {
         fprintf(stderr, "SETVECTITEM: accumulator is null\n");
         exit(1);
     }
    tab[n] = v;
    mv->acc = encode(0);
    mv->pc++;
}

/* @requires mv points to a valid VM, codes[pc+1]=n, codes[pc+2]=p,
             mv->tab_globals[n] points to a valid block
   @assigns  mv->acc, mv->pc
   @ensures  loads mv->tab_globals[n][p] into accumulator */
void GETGLOBALFIELD(vm *mv){
    int n = mv->codes[mv->pc + 1];
    int p = mv->codes[mv->pc + 2];
    value *tab = (value*)mv->tab_globals[n];
    if(!tab) {
         fprintf(stderr, "GETGLOBALFIELD: tab is null\n");
         exit(1);
     }
    mv->acc = tab[p];
    mv->pc += 3;
}

/* @requires mv points to a valid VM with stack not full, codes[pc+1]=n, codes[pc+2]=p,
             mv->tab_globals[n] points to a valid block
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes acc, then loads mv->tab_globals[n][p] into accumulator */
void PUSHGETGLOBALFIELD(vm *mv){
    push(mv, mv->acc); // push the content of the accumulator
    int n = mv->codes[mv->pc + 1];
    int p = mv->codes[mv->pc + 2];
    value *tab = (value*)mv->tab_globals[n];
    if(!tab) {
         fprintf(stderr, "PUSHGETGLOBALFIELD: tab is null\n");
         exit(1);
     }
    mv->acc = tab[p];
    mv->pc += 3;
}

/* @requires mv points to a valid VM, accumulator points to a valid block whose
             field 0 holds an encoded integer m
   @assigns  mv->acc, mv->pc
   @ensures  replaces block[0] with encode(m + n), sets acc to encode(0) */
void OFFSETREF(vm *mv){
    int n = mv->codes[mv->pc + 1];
    value *tab = (value*)mv->acc;
    if(!tab) {
         fprintf(stderr, "OFFSETREF: tab is null\n");
         exit(1);
     }
    long m = decode(tab[0]);
    tab[0] = encode((int)m + n);
    mv->acc = encode(0);
    mv->pc += 2;
}

/* @requires mv points to a valid VM whose tab_atoms is initialized
   @assigns  mv->acc, mv->pc
   @ensures  loads (value)mv->tab_atoms[0] into the accumulator */
void ATOM0(vm *mv){
    mv->acc = (value)mv->tab_atoms[0];
    mv->pc++;
}

/* @requires mv points to a valid VM whose tab_atoms is initialized,
             codes[pc+1] is a valid atom index
   @assigns  mv->acc, mv->pc
   @ensures  loads (value)mv->tab_atoms[n] into the accumulator */
void ATOM(vm *mv){
    int n = mv->codes[mv->pc + 1];
    mv->acc = (value)mv->tab_atoms[n];
    mv->pc += 2;
}

/* @requires mv points to a valid VM with stack not full, tab_atoms is initialized
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes acc, then loads (value)mv->tab_atoms[0] */
void PUSHATOM0(vm *mv){
    push(mv, mv->acc);
    mv->acc = (value)mv->tab_atoms[0];
    mv->pc++;
}

/* @requires mv points to a valid VM with stack not full, tab_atoms is initialized,
             codes[pc+1] is a valid atom index
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes acc, then loads (value)mv->tab_atoms[n] */
void PUSHATOM(vm *mv){
    push(mv, mv->acc);
    int n = mv->codes[mv->pc + 1];
    mv->acc = (value)mv->tab_atoms[n];
    mv->pc += 2;
}
