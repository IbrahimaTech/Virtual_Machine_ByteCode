#include <stdio.h>
#include <stdlib.h>
#include "primitives.h"

/* @requires mv points to a valid VM
   @assigns  mv->tab_atoms
   @ensures  fills mv->tab_atoms with 256 atoms (each obtained via malloc(0)) */
void atoms(vm *mv){
    for(int i = 0; i < 256; i++){
        mv->tab_atoms[i] = malloc(0);
    }
}

/* @requires arg points to an array of at least nb_arg values, num and nb_arg are valid
   @assigns  may write to streams (stdout, stderr) depending on the primitive
   @ensures  returns the value produced by the primitive call, or encode(0) on
             an unrecognized primitive */
value call_primitive(int num, value *arg, int nb_arg){
     if(num == 15 && nb_arg == 2){
        long n = decode(arg[0]);
        value *tab = (value*)malloc(sizeof(value) * n);
        // if malloc fails
        if (!tab) {
            perror("malloc primitive 15");
            exit(1);
        }
        for (long i = 0; i < n; i++){
            tab[i] = arg[1];
        }
        return (value)tab;
     }

     if(num == 288 && nb_arg == 1){
        fflush((FILE*)arg[0]);
        return encode(0);
     }

     if(num == 293 && nb_arg == 1){
        int c = fgetc((FILE *)arg[0]); // read one character from the stream and return
        // its ASCII code
        return encode(c);
     }

     if(num == 302 && nb_arg == 1 && arg[0] == (value)1){
         return (value)stdin;
     }

     if(num == 304 && nb_arg == 1){
        if(arg[0] == encode(1)){
            return (value)stdout;
        }
        if(arg[0] == encode(2)){
            return (value)stderr;
        }
     }

     if(num == 310 && nb_arg == 2){
        int n = (int)decode(arg[1]);
        FILE *f = (FILE*)arg[0];
        if(f != NULL){
            fputc(n, f); // write the character with ASCII code n on f
            fflush(f); // force the character to be displayed immediately
        }
         return encode(0);
     }

     else{ // avoid hanging when an unknown primitive is called
        fprintf(stderr, "Error in primitive call, returning 1");
        return encode(0);
     }

}
