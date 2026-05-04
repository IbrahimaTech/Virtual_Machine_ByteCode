#ifndef VM_H
#define VM_H

#include "types.h"

/* Print the machine state */
/* @requires mv points to a valid VM
   @assigns  nothing
   @ensures  prints the index, accumulator, stack content (top first) and global
             values to standard output, exactly in the format expected by the subject */
void display_vm(vm *mv);

#endif
