/**************************************************************
 *
 *                     readaline.c
 *
 *     Assignment: Homework 1
 *     Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 *     Date: Sept 21 2021
 *
 *     summary
 *
 *     Contains the implementation of the readaline program.
 *
 **************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "readaline.h"


Except_T Runtime_Error = { "Checked runtime error" };

int readaline(FILE *inputfd, char **datapp) {
    //printf("1 readaline");
    int currMemory = 1000;
    int byteCounter = 0;
    TRY 
        if (inputfd == NULL || datapp == NULL) {
            RAISE (Runtime_Error);
        }

        char *lineArray = (char*) malloc(currMemory);
        
        if (lineArray == NULL) {
            RAISE(Runtime_Error);
        }

        bool sameLine = true;
        char current;
        int i = 0;
        
        while (sameLine && fscanf(inputfd, "%c", &current) == 1 ) {
            byteCounter += 1;
        
            if (current == '\n') {
                lineArray[i] = current;
                sameLine = false;
            }
            else{
                lineArray[i] = current;
                i++;
                // if (i == currMemory) {
                //     currMemory *= 2;
                //     printf("seg fault?\n");
                //     lineArray = realloc(lineArray, currMemory);
                // }
            }
        }
        *datapp = lineArray;

    EXCEPT( Runtime_Error ) {
        fprintf(stderr,  "Checked Runtime Error");
    };

    END_TRY;
    return byteCounter;
}