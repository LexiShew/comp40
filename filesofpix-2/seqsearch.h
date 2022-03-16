/**************************************************************
 *
 *                     seqsearch.h
 *
 *     Assignment: Homework 1
 *     Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 *     Date: Sept 21 2021
 *
 *     summary
 *
 *     Contains the interface of the first phase of restoration,
 *     which is searching for the correct injection sequence.
 *
 **************************************************************/


#ifndef SEQSEARCH_INCLUDED
#define SEQSEARCH_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <except.h>
#include <atom.h>
#include <table.h>
#include <seqsearch.h>
#include <stdbool.h>
#include "readaline.h"
#include "charextraction.h"


/* 
 * input:
 * output:
 * purpose:
*/
extern char *searchForSequence(bool *sequenceFound, FILE *file, char *datapp, 
                                  Table_T injTable, char **first_instance, char **second_instance, int * width);

#endif