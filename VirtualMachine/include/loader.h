#ifndef LOADER_H
#define LOADER_H

#include "types.h"

/* Load and extract the bytecode information into the virtual machine */
/* @requires mv points to a valid VM, file is a non-NULL path string
   @assigns  mv->nb_codes, mv->codes, mv->nb_globals, mv->tab_globals
   @ensures  reads the .sobf file and populates the VM. Returns 1 on success,
             0 on any failure (invalid format, IO error, allocation failure) */
int read_extract_file(vm *mv, char *file);

#endif
