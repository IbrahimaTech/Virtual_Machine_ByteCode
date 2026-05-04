#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "stack.h"
#include "loader.h"
#include "primitives.h"
#include "engine.h"
#include "vm.h"

int main(int argc, char *argv[]){
    /* Zero-initialize every field of the VM (codes/globals/stack pointers to NULL,
       counters to 0, every entry of tab_atoms[256] to NULL). */
    vm machine = {NULL, 0, NULL, 0, 0, NULL, 0, 0, 0, 0, {NULL}};

    init_stack(&machine); /* allocate the value stack */
    atoms(&machine);      /* allocate the 256 atoms inside the VM */

    int print_end = 0; /* flag: print the final VM state if --print-end-machine is given */

    if(argc < 2 || argc > 3){
        printf("\nUsage: %s file.sobf [--print-end-machine]\n", argv[0]);
        for(int i = 0; i < 256; i++) free(machine.tab_atoms[i]);
        if (machine.stack) free(machine.stack);
        return 1;
    }

    if(argc == 3 && strcmp(argv[2], "--print-end-machine") == 0){
        print_end = 1;
    }

    /* Verify the input file is well-formed and load it into the VM. */
    if(!read_extract_file(&machine, argv[1])){
        printf("\nInvalid file: %s\n", argv[1]);
        for(int i = 0; i < 256; i++) free(machine.tab_atoms[i]);
        if (machine.stack) free(machine.stack);
        return 1;
    }

    value accumul = virtual_machine(&machine);

    if(print_end == 1){
        display_vm(&machine);
    } else {
        printf("\nAccumulator: %ld\n", accumul);
    }

    /* Free the 256 atoms encapsulated in the VM. */
    for(int i = 0; i < 256; i++){
        free(machine.tab_atoms[i]);
    }

    /* Free everything else allocated during the run. */
    free(machine.codes);
    free(machine.tab_globals);
    free(machine.stack);

    return 0;
}
