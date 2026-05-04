#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "stack.h"
#include "instr_arithmetic.h"

/* @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  loads encode(0) into the accumulator */
void CONST0(vm *mv){
    mv->acc = encode(0);
    mv->pc += 1;
}

/* @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  loads encode(1) into the accumulator */
void CONST1(vm *mv){
    mv->acc = encode(1);
    mv->pc += 1;
}

/* @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  loads encode(2) into the accumulator */
void CONST2(vm *mv){
    mv->acc = encode(2);
    mv->pc += 1;
}

/* @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  loads encode(3) into the accumulator */
void CONST3(vm *mv){
    mv->acc = encode(3);
    mv->pc += 1;
}

/* @requires mv points to a valid VM, mv->codes[mv->pc + 1] is an integer n
   @assigns  mv->acc, mv->pc
   @ensures  loads encode(n) into the accumulator, mv->pc += 2 */
void CONSTINT(vm *mv){
    int n = mv->codes[mv->pc + 1];
    mv->acc = encode(n);
    mv->pc += 2;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads encode(0) into the accumulator */
void PUSHCONST0(vm *mv){
    push(mv, mv->acc);
    mv->acc = encode(0);
    mv->pc += 1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads encode(1) into the accumulator */
void PUSHCONST1(vm *mv){
    push(mv, mv->acc);
    mv->acc = encode(1);
    mv->pc += 1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads encode(2) into the accumulator */
void PUSHCONST2(vm *mv){
    push(mv, mv->acc);
    mv->acc = encode(2);
    mv->pc += 1;
}

/* @requires mv points to a valid VM with stack not full
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads encode(3) into the accumulator */
void PUSHCONST3(vm *mv){
    push(mv, mv->acc);
    mv->acc = encode(3);
    mv->pc += 1;
}

/* @requires mv points to a valid VM with stack not full,
             mv->codes[mv->pc + 1] is an integer n
   @assigns  mv->stack, mv->top, mv->acc, mv->pc
   @ensures  pushes the accumulator, then loads encode(n) into the accumulator */
void PUSHCONSTINT(vm *mv){
    int n = mv->codes[mv->pc + 1];
    push(mv, mv->acc);
    mv->acc = encode(n);
    mv->pc += 2;
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->acc, mv->pc
   @ensures  replaces the accumulator with encode(-n) */
void NEGINT(vm *mv){
    long n = decode(mv->acc);
    mv->acc = encode(-n);
    mv->pc += 1;
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n + m) */
void ADDINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    mv->acc = encode(n + m);
    mv->pc += 1;
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n - m) */
void SUBINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    mv->acc = encode(n - m);
    mv->pc += 1;
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n * m) */
void MULINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    mv->acc = encode(n * m);
    mv->pc += 1;
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m. If m == 0, prints fatal error and exits with code 2;
             otherwise replaces the accumulator with encode(n / m) */
void DIVINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    if(m == 0){
        fprintf(stderr,"Fatal error: exception Division_by_zero\n");
        mv->pc++;
        exit(2); // exit return code
    }
    else{
        mv->acc = encode((long)(n / m));
        mv->pc++;
    }
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m. If m == 0, prints fatal error and exits with code 2;
             otherwise replaces the accumulator with encode(n % m) */
void MODINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    if(m == 0){
        fprintf(stderr,"Fatal error: exception Division_by_zero\n");
        mv->pc++;
        exit(2); // exit return code
    }
    else{
        mv->acc = encode((long)(n % m));
        mv->pc++;
    }
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n & m) */
void ANDINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    mv->acc = encode((long)(n & m)); // bitwise AND of n and m
    mv->pc += 1;
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n | m) */
void ORINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    mv->acc = encode((long)(n | m)); // bitwise OR of n and m
    mv->pc += 1;
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n ^ m) */
void XORINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    // bitwise exclusive OR of n and m
    mv->acc = encode((long)(n ^ m));
    mv->pc += 1;
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with encode(n << m) */
void LSLINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    // shift n left by m bits
    mv->acc = encode((long)(n << m));
    mv->pc += 1;
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with logical right shift of n by m bits */
void LSRINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    // shift n right by m bits, sign not preserved
    // (we cast to unsigned to perform a logical shift)
    mv->acc = encode((unsigned long)n >> m);
    mv->pc += 1;
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, replaces the accumulator with arithmetic right shift of n by m bits */
void ASRINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    // shift n right by m bits, sign preserved
    mv->acc = encode((long)n >> m);
    mv->pc += 1;
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if n < m else encode(0) */
void LTINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    if(n < m){
        mv->acc = encode(1);
        mv->pc +=1;
    }
    else{
        mv->acc = encode(0);
        mv->pc += 1;
    }
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if n <= m else encode(0) */
void LEINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    if(n <= m){
        mv->acc = encode(1);
        mv->pc +=1;
    }
    else{
        mv->acc = encode(0);
        mv->pc += 1;
    }
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if n > m else encode(0) */
void GTINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    if(n > m){
        mv->acc = encode(1);
        mv->pc +=1;
    }
    else{
        mv->acc = encode(0);
        mv->pc += 1;
    }
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if n >= m else encode(0) */
void GEINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    if(n >= m){
        mv->acc = encode(1);
        mv->pc +=1;
    }
    else{
        mv->acc = encode(0);
        mv->pc += 1;
    }
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if (unsigned)n < (unsigned)m else encode(0) */
void ULTINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    if((unsigned long)n < (unsigned long)m){ // unsigned comparison
        mv->acc = encode(1);
        mv->pc +=1;
    }
    else{
        mv->acc = encode(0);
        mv->pc += 1;
    }
}

/* @requires mv points to a valid VM, accumulator and stack top are encoded ints
   @assigns  mv->acc, mv->stack, mv->top, mv->pc
   @ensures  pops m, accumulator becomes encode(1) if (unsigned)n >= (unsigned)m else encode(0) */
void UGEINT(vm *mv){
    long n = decode(mv->acc);
    long m = decode(pop(mv));
    if((unsigned long)n >= (unsigned long)m){ // unsigned comparison
        mv->acc = encode(1);
        mv->pc +=1;
    }
    else{
        mv->acc = encode(0);
        mv->pc += 1;
    }
}

/* @requires mv points to a valid VM, accumulator holds an encoded integer
   @assigns  mv->acc, mv->pc
   @ensures  replaces the accumulator with encode(n + m), m is read from codes[pc+1] */
void OFFSETINT(vm *mv){
    long n = decode(mv->acc);
    int m = mv->codes[mv->pc + 1];
    mv->acc = encode(n + (long)m); // cast to homogenize the sum types
    mv->pc += 2;
}

/* @requires mv points to a valid VM
   @assigns  mv->acc, mv->pc
   @ensures  if accumulator is odd (encoded integer), accumulator becomes encode(1)
             else encode(0) */
void ISINT(vm *mv){
    if(mv->acc % 2 == 1){
        mv->acc = encode(1);
        mv->pc += 1;
    }
    else{
        mv->acc = encode(0);
        mv->pc += 1;
    }
}
