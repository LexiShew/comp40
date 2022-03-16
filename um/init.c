/*****************************************************************************
 *
 *                                  init.c
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the implementation for our initiation of our UM. It contains a
 *      function, get_m0, that fills in the m[0] instruction array from
 *      the .um binary by taking in the name of the .um, the address of the
 *      uint32_t array representing m[0], and the length of this array, then
 *      filling the array with each word (converting from the big endian of
 *      the file to the machine's little endian format).
 *
 ****************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "init.h"


/*
 * pack_word
 * Behavior: packs the four chars from chars into a uint32_t word, returns word
 * Parameters: unsigned char chars[4] -- array of four unsigned chars
 *                                       representing one word
 * Expectations/errors: all four elements of chars should be initialized
 * Implementation: bitshifts each char over and adds next one to pack into one
 *                 word
 */
uint32_t pack_word(unsigned char chars[4]) {
    uint32_t word = 0;
    for (int i = 0; i < 4; i++) {
        word <<= 8;
        word |= chars[i];
    }
    return word;
}

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
 * Implementation: gets characters, packs into one word, puts each word into
 *                 m0_array
 */
void get_m0(char *filename, uint32_t *m0_array, int num_elem)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    int c = fgetc(fp);
    unsigned char chars[4];
    for (int i = 0; i < num_elem; i++) {
        for (int j = 0; j < 4; j++) {
            if (feof(fp)) {
                fprintf(stderr, "Error: file bad\n");
                exit(EXIT_FAILURE);
            }
            chars[j] = c;
            c = fgetc(fp);
        }
        m0_array[i + 1] = pack_word(chars);
    }
    fclose(fp);
}