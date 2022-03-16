/**************************************************************
 *
 *                     word-file.h
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * Header file for word-file.c which can write a compressed
 * binary image to standard output and read in the header
 * of a compressed file.
 *
 **************************************************************/

#include "a2methods.h"
#include <stdio.h>

/*
 * file_to_word_A2
 * Behavior: reads in a file and puts the info into an A2 of words
 * Parameters: FILE *fp
 * Returns: A2 of words from the file
 * Expectations/errors: fp is not null
 */
extern A2Methods_UArray2 file_to_word_A2(FILE *fp);

/*
 * word_to_file
 * Behavior: write binary image to stdout
 * Parameters: A2 word_A2 - an A2 of words
 * Returns: none
 * Expectations/errors: word_A2 should not be null
 */
extern void word_to_file(A2Methods_UArray2 word_A2);