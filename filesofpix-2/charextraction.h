/**************************************************************
 *
 *                     charextraction.h
 *
 *     Assignment: Homework 1
 *     Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 *     Date: Sept 21 2021
 *
 *     summary
 *     Implementation of character extraction program. 
 *     
 * 
 *
 **************************************************************/

#ifndef CHAREXTRACTION_INCLUDED
#define CHAREXTRACTION_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <except.h>
#include <atom.h>
#include <table.h>
#include <seqsearch.h>
#include <stdbool.h>


/* 
 * input:
 * output:
 * purpose:
*/
extern char *extractLetters (char *allChars, int *charsLength);


/* extractNumbers
 * input: a pointer to a cstring
 * output: 
 * purpose:
*/
extern char *extractNumbers(char *allChars, int *numsLength);

/* 
 * input:
 * output:
 * purpose:
*/
extern bool isNum(char current);

/* 
 * input:
 * output:
 * purpose:
*/
extern size_t stringSize(const char *str);

#endif