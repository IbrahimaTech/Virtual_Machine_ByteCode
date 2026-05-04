#ifndef TYPES_H
#define TYPES_H

/* BASE TYPES */
typedef int code;
typedef long int value;

/* VIRTUAL MACHINE STRUCTURE
   Defined exactly once here (in the header) so that the C One Definition Rule
   is respected: every .c file that includes types.h sees the same definition.

   The tab_atoms array is encapsulated as a field of the VM struct, which
   avoids any global variable (no extern keyword needed). */
typedef struct VM {
    code *codes;            /* array of program instructions */
    int nb_codes;           /* total number of instructions */

    value *tab_globals;     /* array of global values */
    int nb_globals;         /* number of global variables */

    int max_stack_size;     /* maximum stack capacity */
    value *stack;           /* execution stack */
    int top;                /* index of the top of the stack */

    int pc;                 /* program counter (index of the current instruction) */
    value acc;              /* accumulator value */
    int running;            /* machine running state (0 = stopped, 1 = running) */

    void *tab_atoms[256];   /* 256 atoms (encapsulated inside the VM) */
} vm;

/* Integer encoding: an integer n is represented as 2*n + 1 (always odd). */
/* @requires nothing
   @assigns  nothing
   @ensures  returns 2*n + 1 */
static inline value encode(long n) {
    return (value)(2 * n + 1);
}

/* Decoding: recover the original integer with (v - 1) / 2. */
/* @requires v is a valid encoded value
   @assigns  nothing
   @ensures  returns (v - 1) / 2 */
static inline long decode(value v) {
    return (long)(v - 1) / 2;
}

#endif
