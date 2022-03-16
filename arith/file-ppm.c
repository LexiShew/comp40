/**************************************************************
 *
 *                     file-ppm.c
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * Reads in, makes, and prints out ppm files.
 * Contains implementation for:
 *      read_in_and_make_ppm
 *      print_ppm_to_stdout
 *
 **************************************************************/

#include "assert.h"
#include "a2plain.h"
#include <stdio.h>
#include "file-ppm.h"
#include "a2methods.h"
#include <mem.h>
#include "pnm.h"

typedef A2Methods_UArray2 A2;

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
Pnm_ppm read_in_and_make_ppm(FILE *input) {
    assert(input != NULL);
    A2Methods_T meth = uarray2_methods_plain;

    Pnm_ppm orig_ppm = Pnm_ppmread(input, meth);
    
    A2 new_A2 = NULL;

    if (orig_ppm->width  % 2 != 0 || orig_ppm->height  % 2 != 0) {
        A2 orig_A2 = orig_ppm->pixels;
        int new_width = meth->width(orig_A2) / 2 * 2;
        int new_height = meth->height(orig_A2) / 2 * 2;
        
        new_A2 = meth->new(new_width, new_height, meth->size(orig_A2));
        
        for (int i = 0; i < new_width; i++) {
            for (int j = 0; j < new_height; j++) {
                *(Pnm_rgb) meth->at(new_A2, i, j) = 
                    *(Pnm_rgb) meth->at(orig_A2, i, j);
            }
        }
        orig_ppm->width = new_width;
        orig_ppm->height = new_height;
        meth->free(&(orig_ppm->pixels));
        orig_ppm->pixels = new_A2; 
    }
    return orig_ppm;
}

/*
 * print_ppm_to_stdout
 * Behavior: generates ppm using information from A2 rgb_A2 and 
 *     prints to standard output
 * Parameters: rgb_A2 - A2 of RGB values
 * Returns: none
 * Expectations/errors: rgb_A2 is not null
 */
void print_ppm_to_stdout(A2 rgb_A2)
{
    assert(rgb_A2 != NULL);
    /*Generate ppm*/
    Pnm_ppm final_ppm;
    NEW(final_ppm);
    
    final_ppm->pixels = rgb_A2;
    final_ppm->methods = uarray2_methods_plain;
    final_ppm->height = uarray2_methods_plain->height(rgb_A2);
    final_ppm->width = uarray2_methods_plain->width(rgb_A2);
    final_ppm->denominator = 255;

    /* Print & free final ppm */
    Pnm_ppmwrite(stdout, final_ppm);
    FREE(final_ppm);
}