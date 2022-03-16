/**************************************************************
 *
 *                     word-file.c
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * This file contains the implementations for writing the
 * compressed binary image to standard output and reading in
 * the header of a compressed file.
 * Functions include:
 *    word_to_file_apply
 *    file_to_word_A2
 *    word_to_file
 *    word_to_file_apply
 *
 **************************************************************/

#include "word-file.h"
#include "a2methods.h"
#include "a2plain.h"
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <mem.h>
#include "bitpack.h"

typedef A2Methods_UArray2 A2;

void word_to_file_apply(int i, int j, A2 word_A2, void *elem, void *cl);

/*
 * file_to_word_A2
 * Behavior: reads in a file and puts the info into an A2 of words
 * Parameters: FILE *fp: pointer to file of bytes
 * Returns: A2 of words from the file
 * Expectations/errors: fp is not null
 */
A2 file_to_word_A2(FILE *fp)
{
    assert(fp != NULL);
    unsigned height, width;
    int read = fscanf(fp, "COMP40 Compressed image format 2\n%u %u", 
                        &width, &height);
 
    assert(read == 2);
    int c = getc(fp);
    assert(c == '\n');

    /*make new A2 to store the words*/
    A2 codeword_A2 = uarray2_methods_plain->new(width / 2, height / 2, 
                                                    sizeof(uint32_t));

    /*put all codewords from fp into a new A2*/
    uint32_t *new_word;
    NEW(new_word);

    int i = 0;
    unsigned char B1 = getc(fp);
    unsigned char B2 = getc(fp);
    unsigned char B3 = getc(fp);
    unsigned char B4 = getc(fp);

    while (!feof(fp)) {
        *new_word = Bitpack_newu(*new_word, 8, 24, B1);
        *new_word = Bitpack_newu(*new_word, 8, 16, B2);
        *new_word = Bitpack_newu(*new_word, 8, 8, B3);
        *new_word = Bitpack_newu(*new_word, 8, 0, B4);

        *(uint32_t*) uarray2_methods_plain->at(codeword_A2, 
                                                i % (width/2), 
                                                i / (width/2)) = *new_word;

        unsigned char *cp = (unsigned char *) new_word;
        cp += 3; /*set cp to be the last byte*/
        unsigned int byte;
        for (byte = 0; byte < 4; byte++) {
            cp--;
        }

        i++;
        B1 = getc(fp);
        B2 = getc(fp);
        B3 = getc(fp);
        B4 = getc(fp);
    }

    FREE(new_word);
    return codeword_A2;
}

/*
 * word_to_file
 * Behavior: write binary image to stdout using an apply function
 *      word_to_file_apply with row major mapping
 * Parameters: A2 word_A2 - an A2 of int32_t codewords
 * Returns: none
 * Expectations/errors: word_A2 should not be null
 */
void word_to_file(A2 word_A2)
{
    assert(word_A2 != NULL);
    /*multiply by 2 to get dim of original image*/
    unsigned width = uarray2_methods_plain->width(word_A2) * 2; 
    unsigned height = uarray2_methods_plain->height(word_A2) * 2;
    printf("COMP40 Compressed image format 2\n%u %u\n", width, height);

    uarray2_methods_plain->map_default(word_A2, word_to_file_apply, NULL);
}

/*
 * word_to_file_apply
 * Behavior: apply function that prints bytes from words in Big Endian order
        to stdout using putchar
 * Parameters: 
        int i: column of word_A2
        int j: row of word_A2
        A2 word_A2: the A2 containing the int32_t codewords
        void *elem: the current codeword being printed out
        void *cl: anything; unused in this function
 * Returns: none
 * Expectations/errors: elem should not be null
 */
void word_to_file_apply(int i, int j, A2 word_A2, void *elem, void *cl)
{
    (void) i;
    (void) j;
    (void) cl;
    (void) word_A2;
    assert(elem != NULL);

    uint32_t *word = (uint32_t*) elem;

    unsigned char *cp = (unsigned char *) word;
    cp += 3; /*set cp to be the last byte*/
  
    unsigned int byte;
    for (byte = 0; byte < 4; byte++) {
        putchar(*cp);
        cp--;
    }
}