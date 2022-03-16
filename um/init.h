#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED


/*****************************************************************************
 *
 *                                  init.h
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the interface for init, a module that reads from an input .um
 *      binary and fills in an array representing the m[0] instructions.
 *      There is one public function: get_m0, which fills an input uint32_t
 *      array with instruction words.
 *
 ****************************************************************************/


#include <stdint.h>


/*
 * get_m0
 * Behavior: fills m0_array with the words from the file specified by filename
 * Parameters:
 *      * char *filename -- the filename of the instructions file
 *      * uint32_t *m0_array -- the array to be filled with the words from the
 *                              file
 *      * int num_elem -- the number of words in filename
 * Expectations/errors: filename must be a readable file, m0_array must be an
 *                      array with size num_elem
 */
extern void get_m0(char *filename, uint32_t *m0_array, int num_elem);

#endif