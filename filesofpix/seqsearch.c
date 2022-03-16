/**************************************************************
 *
 *                     seqsearch.c
 *
 *     Assignment: Homework 1
 *     Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 *     Date: Sept 21 2021
 *
 *     summary
 *
 *     Contains the implementation of the first phase of restoration,
 *     which is searching for the correct injection sequence.
 *
 **************************************************************/


#include "seqsearch.h"


char *searchForSequence(bool *sequenceFound, FILE *file, char *datapp, 
                                  Table_T injTable, char **first_instance, char **second_instance, int * width)
{
    int count = 0;
    char* removeValue;
    int charsLength = 0;
    while (!*sequenceFound) {
        count++;
        readaline(file, &datapp);
        char *allChars = datapp;
                
        char *currLetters = extractLetters(allChars, &charsLength);
        //printf("Current Sequence: %s", currLetters);
        const char *letterAtom = (char*) Atom_new(currLetters, charsLength);

     
        removeValue = (char*) Table_remove(injTable, letterAtom);  
        Table_put(injTable, letterAtom, allChars);

        if (removeValue != NULL) {
            //it is duplicated//
            *sequenceFound = true;
            

            *first_instance = extractNumbers(removeValue,width);
            *second_instance = extractNumbers(allChars,width);
            
            // printf("SEQSEARCH value of first instance: %s\n", *first_instance);
            // printf("SEQSEARCH value of first instance: %s\n", *second_instance);
        }
        free(currLetters);
    }
    
    

    return extractLetters(removeValue, &charsLength);
}