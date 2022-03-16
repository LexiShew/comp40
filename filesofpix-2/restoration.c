/**************************************************************
 *
 *                     restoration.c
 *
 *     Assignment: Homework 1
 *     Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 *     Date: Sept 21 2021
 *
 *     summary
 *
 *     Contains the implementation of the restoration program.

 *     1. Ask about how to raise "default" checked runtime error using try except 
 *       yes i have read the book i just dont understand it
 *     2. Ask about why turing broken
 
 *
 **************************************************************/


/*  TO DO 
    * where should 'checked runtime error' be output? stderr?
    fprintf sterr
    * error while reading file
    * what is errno? how do you check when this fscanf fails?
    check piazza
    * should we be defining our functions below main
    make a .h make other .c files
    * how should we be commenting
        .h should have input/output
        .c shou.d have implementation specifics
*/

/* NEXT STEPS
    * memory leaks
        * atom
    * assertions? 
    *   checked runtime error option
    * exceptions -- dont have to use -- just do assert
    * exit(0)
    * have a check for uncorrupted pgms        

*/



#include <stdio.h>
#include <stdlib.h>
#include <except.h>
#include <atom.h>
#include <table.h>
#include <seq.h>
#include <seqsearch.h>
#include <stdbool.h>

#include "charextraction.h"
#include "readaline.h"
#include "pgmGenerator.h"

// Except_T Restoration_Runtime_Error = { "Checked runtime error" };
void freeTableData(Table_T table)
{
    (void) table;
}


int restore(int argc, char* argv[])
{
    FILE *file;
    if (argc == 1) {  
        file = stdin;
    } 
    else if (argc == 2) { 
        file = fopen(argv[1], "rb");
    } 
    else {
        /* throw argument error */
        printf("insufficient arguments\n");
        return 0;
    }

    if (file == NULL) {
        printf("file not found\n");
        return 0;
    } 
    char *datapp = NULL;

    Seq_T resultSeq = Seq_new(1000);  

    /*  stores Atoms of injected sequences as the key and the whole line
        associated as the value */
    Table_T injTable = Table_new(1000, NULL, NULL);
    
    /*  if the correct injection sequence is found, this is set to 1    */
    bool sequenceFound = false;    
    int width;

    /*  stores the correct injection sequence */
    char *first_instance = NULL;
    char *second_instance = NULL;
    char *injSequence = searchForSequence(&sequenceFound, file, datapp, injTable, &first_instance, &second_instance, &width);
    char *injAtom = (char*) Atom_new(injSequence, stringSize(injSequence));
   
    if (sequenceFound == true) {        
        Seq_addhi(resultSeq, first_instance);
        Seq_addhi(resultSeq, second_instance);
        
        int height = 2;

        findOriginal(&resultSeq, &datapp, file, injAtom, &height);
        printResult(&resultSeq, height, width);
        freeTableData(injTable);
    }

    // free(first_instance);
    // free(second_instance);
    free(datapp);

    Seq_free(&resultSeq);
    Table_free(&injTable);
    fclose(file);
    
    return 0;
}


int main(int argc, char* argv[]) {
    restore(argc, argv);
}