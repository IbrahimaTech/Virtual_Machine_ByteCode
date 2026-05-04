#include "types.h"
#include "instr_memory.h"
#include "engine_eval_memory.h"

/* @requires mv points to a valid VM, instruction is the opcode at mv->codes[mv->pc]
   @assigns  mv->pc, mv->acc, mv->stack, mv->top, mv->tab_globals (depending on the opcode)
   @ensures  if instruction belongs to the "memory" category, executes it via the
             local switch and returns 1; otherwise returns 0 without touching mv */
int engine_eval_memory(vm *mv, int instruction){
    switch(instruction){
        /* GETGLOBAL */
        case 53:{
            GETGLOBAL(mv);
            return 1;
        }
        /* PUSHGETGLOBAL */
        case 54:{
            PUSHGETGLOBAL(mv);
            return 1;
        }
        /* SETGLOBAL */
        case 57:{
            SETGLOBAL(mv);
            return 1;
        }
        /* GETGLOBALFIELD */
        case 55:{
            GETGLOBALFIELD(mv);
            return 1;
        }
        /* PUSHGETGLOBALFIELD */
        case 56:{
            PUSHGETGLOBALFIELD(mv);
            return 1;
        }
        /* MAKEBLOCK */
        case 62:{
            MAKEBLOCK(mv);
            return 1;
        }
        /* MAKEBLOCK1 */
        case 63:{
            MAKEBLOCK1(mv);
            return 1;
        }
        /* MAKEBLOCK2 */
        case 64:{
            MAKEBLOCK2(mv);
            return 1;
        }
        /* MAKEBLOCK3 */
        case 65:{
            MAKEBLOCK3(mv);
            return 1;
        }
        /* GETFIELD0 */
        case 67:{
            GETFIELD0(mv);
            return 1;
        }
        /* GETFIELD1 */
        case 68:{
            GETFIELD1(mv);
            return 1;
        }
        /* GETFIELD2 */
        case 69:{
            GETFIELD2(mv);
            return 1;
        }
        /* GETFIELD3 */
        case 70:{
            GETFIELD3(mv);
            return 1;
        }
        /* GETFIELD */
        case 71:{
            GETFIELD(mv);
            return 1;
        }
        /* SETFIELD0 */
        case 73:{
            SETFIELD0(mv);
            return 1;
        }
        /* SETFIELD1 */
        case 74:{
            SETFIELD1(mv);
            return 1;
        }
        /* SETFIELD2 */
        case 75:{
            SETFIELD2(mv);
            return 1;
        }
        /* SETFIELD3 */
        case 76:{
            SETFIELD3(mv);
            return 1;
        }
        /* SETFIELD */
        case 77:{
            SETFIELD(mv);
            return 1;
        }
        /* GETVECTITEM */
        case 80:{
            GETVECTITEM(mv);
            return 1;
        }
        /* SETVECTITEM */
        case 81:{
            SETVECTITEM(mv);
            return 1;
        }
        /* OFFSETREF */
        case 128:{
            OFFSETREF(mv);
            return 1;
        }
        /* ATOM0 */
        case 58:{
            ATOM0(mv);
            return 1;
        }
        /* ATOM */
        case 59:{
            ATOM(mv);
            return 1;
        }
        /* PUSHATOM0 */
        case 60:{
            PUSHATOM0(mv);
            return 1;
        }
        /* PUSHATOM */
        case 61:{
            PUSHATOM(mv);
            return 1;
        }
        default:
            /* Not a memory opcode: this is the last evaluator, so the caller
               will treat a 0 return as an unknown opcode. */
            return 0;
    }
}
