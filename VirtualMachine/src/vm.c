#include <stdio.h>
#include "vm.h"

/* @requires mv points to a valid VM
   @assigns  nothing
   @ensures  prints the index, accumulator, stack content (top first) and global
             values to standard output, exactly in the format expected by the subject */
void display_vm(vm *mv){
    // Here we follow the output format expected by the project specification
    printf("\nIndex: %d\n", mv->pc);

    // print the accumulator value as a long, more human-readable than the raw bytes
    printf("Accumulator: %ld\n", mv->acc);

    printf("Stack:\n");
    for(int i = mv->top; i >= 0; i-=1){
        printf("%ld\n", mv->stack[i]);
    }

    printf("Global:\n");
    for(int i = 0; i < mv->nb_globals; i+=1){
        printf("%d %ld\n", i, mv->tab_globals[i]);
    }
}
