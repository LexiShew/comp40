/**************************************************************
 *
 *                     file-ppm.h
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * Header file for file-ppm.c.
 * Contains function declarations for:
 *      read_in_and_make_ppm
 *      print_ppm_to_stdout
 * Includes typedef:
*       A2Methods_UArray2 A2
 *
 **************************************************************/

#include <stdio.h>
#include "pnm.h"

/*
 * read_in_and_make_ppm
 * Behavior: 
        Reads in a ppm file and returns a Pnm_ppm struct
        Trims image if number of columns or rows is uneven
 * Parameters: 
        FILE *input - pointer to ppm file
 * Returns: Pnm_ppm struct from the inputted file
 * Expectations/errors: 
        input file should not be null
 */
extern Pnm_ppm read_in_and_make_ppm(FILE *input);

/*
 * print_ppm_to_stdout
 * Behavior: generates ppm and prints to standard output
 * Parameters: rgb_A2
 * Returns: none
 * Expectations/errors: rgb_A2 is not null
 */
extern void print_ppm_to_stdout(A2Methods_UArray2 rgb_A2);