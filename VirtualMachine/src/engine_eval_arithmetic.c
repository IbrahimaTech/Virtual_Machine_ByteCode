#include "types.h"
#include "instr_arithmetic.h"
#include "engine_eval_arithmetic.h"

/* @requires mv points to a valid VM, instruction is the opcode at mv->codes[mv->pc]
   @assigns  mv->pc, mv->acc, mv->stack, mv->top (depending on which opcode is executed)
   @ensures  if instruction belongs to the "arithmetic" category, executes it via
             the local switch and returns 1; otherwise returns 0 without touching mv */
int engine_eval_arithmetic(vm *mv, int instruction){
    switch(instruction){
        /* CONST0 */
        case 99:{
            CONST0(mv);
            return 1;
        }
        /* CONST1 */
        case 100:{
            CONST1(mv);
            return 1;
        }
        /* CONST2 */
        case 101:{
            CONST2(mv);
            return 1;
        }
        /* CONST3 */
        case 102:{
            CONST3(mv);
            return 1;
        }
        /* CONSTINT */
        case 103:{
            CONSTINT(mv);
            return 1;
        }
        /* PUSHCONST0 */
        case 104:{
            PUSHCONST0(mv);
            return 1;
        }
        /* PUSHCONST1 */
        case 105:{
            PUSHCONST1(mv);
            return 1;
        }
        /* PUSHCONST2 */
        case 106:{
            PUSHCONST2(mv);
            return 1;
        }
        /* PUSHCONST3 */
        case 107:{
            PUSHCONST3(mv);
            return 1;
        }
        /* PUSHCONSTINT */
        case 108:{
            PUSHCONSTINT(mv);
            return 1;
        }
        /* NEGINT */
        case 109:{
            NEGINT(mv);
            return 1;
        }
        /* ADDINT */
        case 110:{
            ADDINT(mv);
            return 1;
        }
        /* SUBINT */
        case 111:{
            SUBINT(mv);
            return 1;
        }
        /* MULINT */
        case 112:{
            MULINT(mv);
            return 1;
        }
        /* DIVINT */
        case 113:{
            DIVINT(mv);
            return 1;
        }
        /* MODINT */
        case 114:{
            MODINT(mv);
            return 1;
        }
        /* ANDINT */
        case 115:{
            ANDINT(mv);
            return 1;
        }
        /* ORINT */
        case 116:{
            ORINT(mv);
            return 1;
        }
        /* XORINT */
        case 117:{
            XORINT(mv);
            return 1;
        }
        /* LSLINT */
        case 118:{
            LSLINT(mv);
            return 1;
        }
        /* LSRINT */
        case 119:{
            LSRINT(mv);
            return 1;
        }
        /* ASRINT */
        case 120:{
            ASRINT(mv);
            return 1;
        }
        /* LTINT */
        case 123:{
            LTINT(mv);
            return 1;
        }
        /* LEINT */
        case 124:{
            LEINT(mv);
            return 1;
        }
        /* GTINT */
        case 125:{
            GTINT(mv);
            return 1;
        }
        /* GEINT */
        case 126:{
            GEINT(mv);
            return 1;
        }
        /* ULTINT */
        case 137:{
            ULTINT(mv);
            return 1;
        }
        /* UGEINT */
        case 138:{
            UGEINT(mv);
            return 1;
        }
        /* OFFSETINT */
        case 127:{
            OFFSETINT(mv);
            return 1;
        }
        /* ISINT */
        case 129:{
            ISINT(mv);
            return 1;
        }
        default:
            /* Not an arithmetic opcode: hand off to the next evaluator. */
            return 0;
    }
}
