#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "types.h"

/* Initialize the 256 atoms of the mv->tab_atoms array */
/* @requires mv points to a valid VM
   @assigns  mv->tab_atoms
   @ensures  fills mv->tab_atoms with 256 atoms (each obtained via malloc(0)) */
void atoms(vm *mv);

/* Primitive dispatcher: call primitive number num with the nb_arg arguments provided */
/* @requires arg points to an array of at least nb_arg values, num and nb_arg are valid
   @assigns  may write to streams (stdout, stderr) depending on the primitive
   @ensures  returns the value produced by the primitive call, or encode(0) on
             an unrecognized primitive */
value call_primitive(int num, value *arg, int nb_arg);

#endif
