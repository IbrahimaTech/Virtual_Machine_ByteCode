#include "types.h"
#include "instr_control.h"
#include "engine_eval_control.h"

/* @requires mv points to a valid VM, instruction is the opcode at mv->codes[mv->pc]
   @assigns  mv->pc, mv->acc, mv->stack, mv->top, mv->running (depending on the opcode)
   @ensures  if instruction belongs to the "control" category, executes it via the
             local switch and returns 1; otherwise returns 0 without touching mv */
int engine_eval_control(vm *mv, int instruction){
    switch(instruction){
        /* STOP */
        case 143:{
            STOP(mv);
            return 1;
        }
        /* CHECK_SIGNALS */
        case 92:{
            CHECK_SIGNALS(mv);
            return 1;
        }
        /* BRANCH */
        case 84:{
            BRANCH(mv);
            return 1;
        }
        /* BRANCHIF */
        case 85:{
            BRANCHIF(mv);
            return 1;
        }
        /* BRANCHIFNOT */
        case 86:{
            BRANCHIFNOT(mv);
            return 1;
        }
        /* SWITCH */
        case 87:{
            SWITCH(mv);
            return 1;
        }
        /* BOOLNOT */
        case 88:{
            BOOLNOT(mv);
            return 1;
        }
        /* EQ */
        case 121:{
            EQ(mv);
            return 1;
        }
        /* NEQ */
        case 122:{
            NEQ(mv);
            return 1;
        }
        /* BEQ */
        case 131:{
            BEQ(mv);
            return 1;
        }
        /* BNEQ */
        case 132:{
            BNEQ(mv);
            return 1;
        }
        /* BLTINT */
        case 133:{
            BLTINT(mv);
            return 1;
        }
        /* BLEINT */
        case 134:{
            BLEINT(mv);
            return 1;
        }
        /* BGTINT */
        case 135:{
            BGTINT(mv);
            return 1;
        }
        /* BGEINT */
        case 136:{
            BGEINT(mv);
            return 1;
        }
        /* BULTINT */
        case 139:{
            BULTINT(mv);
            return 1;
        }
        /* BUGEINT */
        case 140:{
            BUGEINT(mv);
            return 1;
        }
        /* C_CALL1 */
        case 93:{
            C_CALL1(mv);
            return 1;
        }
        /* C_CALL2 */
        case 94:{
            C_CALL2(mv);
            return 1;
        }
        /* C_CALL3 */
        case 95:{
            C_CALL3(mv);
            return 1;
        }
        /* C_CALL4 */
        case 96:{
            C_CALL4(mv);
            return 1;
        }
        /* C_CALL5 */
        case 97:{
            C_CALL5(mv);
            return 1;
        }
        /* C_CALLN */
        case 98:{
            C_CALLN(mv);
            return 1;
        }
        default:
            /* Not a control-flow opcode: hand off to the next evaluator. */
            return 0;
    }
}
