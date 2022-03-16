/**************************************************************
 *
 *                     pgmGenerator.h
 *
 *     Assignment: Homework 1
 *     Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 *     Date: Sept 21 2021
 *
 *     summary
 *
 *     Contains the interface of the pgm genereator, 
 *      which is the second phase of our restoration project.
 *
 **************************************************************/


#ifndef PGMGENERRATOR_INCLUDED
#define PGMGENERATOR_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <except.h>
#include <atom.h>
#include <table.h>
#include <seqsearch.h>
#include <stdbool.h>
#include "charextraction.h"

/* 
 * input:
 * output:
 * purpose:
*/
extern void findOriginal(Seq_T *results, char **datapp, FILE *inputfd, char* realSequence, int *height);

/* 
 * input:
 * output:
 * purpose:
*/
extern void printResult(Seq_T *results, int height, int width);


#endif