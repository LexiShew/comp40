/**************************************************************
 *
 *                     pgmGenerator.c
 *
 *     Assignment: Homework 1
 *     Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 *     Date: Sept 21 2021
 *
 *     summary
 *
 *     Contains the implementation of the pgm generator, 
 *      which is the second phase of our restoration project.
 *
 **************************************************************/

#include <seq.h>
#include "pgmGenerator.h"
#include "readaline.h"
#include "charextraction.h"

void findOriginal(Seq_T *results, char **datapp, FILE *inputfd, char* realSequence, int *height)
{
    
    int lettersLength = readaline(inputfd, datapp);
    //printf("\nbug0\n");
    while ( lettersLength != 0) {
        //printf("\nbug1\n");
        
        char *letters = extractLetters(*datapp, &lettersLength);
        //printf("\nbug1.2\n");
        int empty;
        char *numbers = extractNumbers(*datapp, &empty);

        //printf("\nbug2\n");
        const char *lettersAtom = (char*) Atom_new(letters, stringSize(letters));

        //printf("\nbug3\n");
        if (realSequence == lettersAtom) {
            Seq_addhi(  *results, numbers);
            *height = *height + 1;
        }
        //printf("\nbug4\n");
        //printf("Current Sequence: %s\n", letters);
        lettersLength = readaline(inputfd, datapp);
    }
    //printf("\nbug5\n");
    //printf("\nHEIGHT IS: %d \n",*height);

}


void printResult(Seq_T *results, int height, int width) {
    printf("P5\n");
    printf("%d ", width);
    printf("%d\n", height);
    printf("%d\n", 255);

    for (int i = 0; i < height; i++) {
        char *currSeq = (char*) Seq_get(*results, i);
        for ( int j = 0; j <width; j++) {
            printf("%c",currSeq[j]);
        }
    }
    
}
