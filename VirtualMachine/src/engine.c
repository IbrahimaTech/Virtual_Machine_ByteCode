#include <stdio.h>
#include "types.h"
#include "stack.h"
#include "engine.h"
#include "engine_eval_base.h"
#include "engine_eval_arithmetic.h"
#include "engine_eval_control.h"
#include "engine_eval_memory.h"

/* @requires mv points to a valid VM whose codes array has been populated
   @assigns  mv->pc, mv->acc, mv->running, mv->stack, mv->tab_globals
   @ensures  initializes the VM state, runs the main fetch-evaluate loop by
             dispatching each opcode to the appropriate evaluator module
             (base / arithmetic / control / memory) until STOP, an unknown
             opcode, or pc out of bounds; returns the final accumulator value */
value virtual_machine(vm *mv){
    mv->pc = 0;          /* program counter starts at 0 */
    mv->acc = encode(0); /* initial accumulator value (encodes the integer 0) */
    mv->running = 1;     /* the machine starts in the running state */
    init_stack(mv);      /* the stack is initialized empty */

    /* The loop stops on STOP, on an unknown opcode, or when pc goes out of
       the codes array. Each iteration tries the four evaluators in order;
       as soon as one of them handles the opcode, we 'continue' to fetch
       the next instruction. */
    while(mv->running){
        if(mv->pc >= mv->nb_codes){
            break;
        }

        int instruction = mv->codes[mv->pc]; /* fetch current opcode */

        if(engine_eval_base(mv, instruction)){
            continue;
        }
        if(engine_eval_arithmetic(mv, instruction)){
            continue;
        }
        if(engine_eval_control(mv, instruction)){
            continue;
        }
        if(engine_eval_memory(mv, instruction)){
            continue;
        }

        /* No evaluator recognized this opcode: halt. */
        fprintf(stderr, "\nUnmodeled opcode encountered: %d\n", instruction);
        mv->running = 0;
    }
    return mv->acc; /* final accumulator value */
}
