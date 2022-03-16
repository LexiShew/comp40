/**************************************************************
 *
 *                     bit-word.h
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * This is our implementation to accompany compressed-word.c.
 * Function declarations include:
 *   compressed_to_word_A2
 *   word_to_compressed_A2
 * Struct declarations include:
 *   Compressed_struct
 *
 **************************************************************/

#include <stdint.h>
#include "a2methods.h"


typedef struct Compressed_struct {
    float a;
    float b;
    float c;
    float d;
    unsigned pb_index;
    unsigned pr_index;
} *Compressed_struct;


/*
 * compressed_to_word_A2
 * Behavior: converts an A2 of compressed values to an A2 of words
 * Parameters: A2 compressed_A2
 * Returns: A2 of words
 * Expectations/errors: compressed_A2 should not be null
 */
extern A2Methods_UArray2 compressed_to_word_A2(A2Methods_UArray2
                                                        compressed_A2);

/*
 * word_to_compressed_A2
 * Behavior: converts an A2 of words to an A2 of compressed values
 * Parameters: A2 word_A2
 * Returns: A2 of compressed values
 * Expectations/errors: word_A2 should not be null
 */
extern A2Methods_UArray2 word_to_compressed_A2(A2Methods_UArray2 word_A2);