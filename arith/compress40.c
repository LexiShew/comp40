/**************************************************************
 *
 *                     compress40.c
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * This is our implementation to accompany compress40.h.
 * It contains the main functions, compress40 and decompress40,
 * which each call helper functions defined in separate files.
 *
 **************************************************************/

#include "compress40.h"
#include "assert.h"
#include <stdio.h>
#include "a2methods.h"
#include "a2plain.h"
#include "pnm.h"
#include <mem.h>

#include "file-ppm.h"
#include "rgb-ypp.h"
#include "ypp-compressed.h"
#include "compressed-word.h"
#include "word-file.h"

typedef A2Methods_UArray2 A2;

/*
 * compress40
 * Behavior: reads from a PPM file and writes compressed image to stdout
 * Parameters: 
    FILE *input: pointer to file to be compressed
 * Expectations/errors: 
    file pointer input is not null
 */
void compress40 (FILE *input) {

    Pnm_ppm origPPM = read_in_and_make_ppm(input); 
    A2 ypp_A2 = rgb_to_ypp_A2(origPPM->pixels, origPPM->denominator); 
    A2 compressed_A2 = ypp_to_compressed_A2(ypp_A2);
    A2 word_A2 = compressed_to_word_A2(compressed_A2);
    word_to_file(word_A2);

    uarray2_methods_plain->free(&word_A2);
    uarray2_methods_plain->free(&compressed_A2);
    uarray2_methods_plain->free(&ypp_A2);
    Pnm_ppmfree(&origPPM);
}

/*
 * decompress40
 * Behavior: reads compressed image from a file pointer and writes the 
    decompressed PPM to standard output
 * Parameters: pointer to compressed file to be decompressed
 * Expectations/errors: 
    file pointer input is not null
 * Implementation
 */
void decompress40(FILE *input) {
    assert(input != NULL);

    A2 word_A2 = file_to_word_A2(input);
    A2 compressed_A2 = word_to_compressed_A2(word_A2);
    A2 ypp_A2 = compressed_to_ypp_A2(compressed_A2);
    A2 rgb_A2 = ypp_to_rgb_A2(ypp_A2); 
    print_ppm_to_stdout(rgb_A2);

    uarray2_methods_plain->free(&word_A2);
    uarray2_methods_plain->free(&rgb_A2);
    uarray2_methods_plain->free(&ypp_A2);
    uarray2_methods_plain->free(&compressed_A2);
}