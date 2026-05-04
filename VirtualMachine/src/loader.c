#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"

/* @requires mv points to a valid VM, file is a non-NULL path string
   @assigns  mv->nb_codes, mv->codes, mv->nb_globals, mv->tab_globals
   @ensures  reads the .sobf file and populates the VM. Returns 1 on success,
             0 on any failure (invalid format, IO error, allocation failure) */
int read_extract_file(vm *mv, char *file){
    FILE *f = fopen(file,"rb"); // open the file in binary read mode
    char s[5] ; // a string buffer

    if(f == NULL){
        return 0;
    }

    // read the first 4 bytes from f into s (the magic header)
    if(fread(s, sizeof(char), 4,f) != 4){
        fclose(f);
        return 0;
    }

    s[4] = '\0'; // null-terminate the string
    // verify the file format is the one expected by our virtual machine
    if(strcmp(s, "SOBF") != 0){
        fclose(f); // close the file
        return 0;
    }

    int c; // declared as int so we can detect EOF
    c = fgetc(f);
    // the loop stops as soon as we read a newline,
    // or when we reach EOF (which prevents an infinite loop)
    while(c != '\n'){
        c = fgetc(f);
    }

    // read the number of codes (code array size) and the number of values
    // (global values array size)
    if(fscanf(f, "%d %d", &mv->nb_codes, &mv->nb_globals) != 2){ // read error
        fclose(f);// close the file
        return 0; // bail out
    }

    c = fgetc(f);
    // the loop stops as soon as we read a newline,
    // or when we reach EOF
    while(c != '\n'){
        c = fgetc(f);
    }

    // allocate memory for the code array and the global values array
    mv->codes = malloc(mv->nb_codes * sizeof(code));
    mv->tab_globals = malloc(mv->nb_globals * sizeof(value));

    // if any allocation failed
    if(!mv->codes || !mv->tab_globals){
        fclose(f);
        return 0;
    }

    // Read the nb_codes code cells from the file directly into mv->codes
    if(fread(mv->codes, sizeof(code), mv->nb_codes, f) != (size_t)mv->nb_codes){
        free(mv->codes);
        free(mv->tab_globals); // free everything we allocated
        fclose(f);
        return 0;
    }

    if (fread(mv->tab_globals, sizeof(value), mv->nb_globals, f) != (size_t)mv->nb_globals) {
        free(mv->tab_globals);
        free(mv->codes); // free everything we allocated
         fclose(f);
         return 0;
    }
    fclose(f);
    return 1; // success
}
