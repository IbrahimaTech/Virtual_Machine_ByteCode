#include "types.h"
#include "instr_base.h"
#include "engine_eval_base.h"

/* @requires mv points to a valid VM, instruction is the opcode at mv->codes[mv->pc]
   @assigns  mv->pc, mv->acc, mv->stack, mv->top (depending on which opcode is executed)
   @ensures  if instruction belongs to the "base" category, executes it via the
             local switch and returns 1; otherwise returns 0 without touching mv */
int engine_eval_base(vm *mv, int instruction){
    switch(instruction){
        /* ACC0 */
        case 0:{
            ACC0(mv);
            return 1;
        }
        /* ACC1 */
        case 1:{
            ACC1(mv);
            return 1;
        }
        /* ACC2 */
        case 2:{
            ACC2(mv);
            return 1;
        }
        /* ACC3 */
        case 3:{
            ACC3(mv);
            return 1;
        }
        /* ACC4 */
        case 4:{
            ACC4(mv);
            return 1;
        }
        /* ACC5 */
        case 5:{
            ACC5(mv);
            return 1;
        }
        /* ACC6 */
        case 6:{
            ACC6(mv);
            return 1;
        }
        /* ACC7 */
        case 7:{
            ACC7(mv);
            return 1;
        }
        /* ACC */
        case 8:{
            ACC(mv);
            return 1;
        }
        /* PUSH */
        case 9:{
            PUSH(mv);
            return 1;
        }
        /* PUSHACC0 */
        case 10:{
            PUSHACC0(mv);
            return 1;
        }
        /* PUSHACC1 */
        case 11:{
            PUSHACC1(mv);
            return 1;
        }
        /* PUSHACC2 */
        case 12:{
            PUSHACC2(mv);
            return 1;
        }
        /* PUSHACC3 */
        case 13:{
            PUSHACC3(mv);
            return 1;
        }
        /* PUSHACC4 */
        case 14:{
            PUSHACC4(mv);
            return 1;
        }
        /* PUSHACC5 */
        case 15:{
            PUSHACC5(mv);
            return 1;
        }
        /* PUSHACC6 */
        case 16:{
            PUSHACC6(mv);
            return 1;
        }
        /* PUSHACC7 */
        case 17:{
            PUSHACC7(mv);
            return 1;
        }
        /* PUSHACC */
        case 18:{
            PUSHACC(mv);
            return 1;
        }
        /* POP */
        case 19:{
            POP(mv);
            return 1;
        }
        /* ASSIGN */
        case 20:{
            ASSIGN(mv);
            return 1;
        }
        default:
            /* The opcode does not belong to this category: tell the caller
               to try the next evaluator. */
            return 0;
    }
}
