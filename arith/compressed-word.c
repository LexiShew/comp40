/**************************************************************
 *
 *                     compressed-word.c
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * This is our implementation to accompany compressed-word.h.
 * These functions pack compressed pixels/blocks into 32-bit
 * words, and unpack them from the 32-bit words as well.
 *
 * This contains the following functions:
 *   compressed_to_word_A2
 *   word_to_compressed_A2
 *
 **************************************************************/
#include "compressed-word.h"
#include "bitpack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "a2plain.h"
#include <mem.h>

typedef A2Methods_UArray2 A2;

void word_to_compressed_apply(int i, int j, A2 word_A2, void *elem, 
                                void *compressed_A2);
void compressed_to_word_apply(int i, int j, A2 compressed_A2, void *elem, 
                                void *word_A2);

/*
 * compressed_to_word_A2
 * Behavior: converts an A2 of compressed values to an A2 of words by using
        an apply function compressed_to_word_apply with row major mapping
 * Parameters: A2 compressed_A2: the A2 of Compressed_structs to be converted
        to words
 * Returns: A2 of words
 * Expectations/errors: compressed_A2 should not be null
 */
A2 compressed_to_word_A2(A2 compressed_A2)
{
    assert(compressed_A2 != NULL);
    int width = uarray2_methods_plain->width(compressed_A2);
    int height = uarray2_methods_plain->height(compressed_A2);

    A2 word_A2 = uarray2_methods_plain->new(width, height, sizeof(uint32_t));
    
    uarray2_methods_plain->map_default(compressed_A2, 
                                        compressed_to_word_apply, word_A2);

    return word_A2;
}

/*
 * word_to_compressed_A2
 * Behavior: converts an A2 of words to an A2 of compressed values using
        an apply function word_to_compressed_apply and row major mapping
 * Parameters: A2 word_A2: A2 of int32_t codewords
 * Returns: A2 of Compressed_structs
 * Expectations/errors: word_A2 should not be null
 */
A2 word_to_compressed_A2(A2 word_A2)
{
    assert(word_A2 != NULL);
    
    int width = uarray2_methods_plain->width(word_A2);
    int height = uarray2_methods_plain->height(word_A2);
    A2 compressed_A2 = uarray2_methods_plain->new(width, height, 
                                        sizeof(struct Compressed_struct));
    
    uarray2_methods_plain->map_default(word_A2, word_to_compressed_apply, 
                                        compressed_A2);

    return compressed_A2;
}

/*
 * convert_compressed_to_word
 * Behavior: packs a compressed component video representation 
     into a 32 bit word using the Bitpack interface
 * Parameters: Compressed_struct comp: the Compressed_struct from the ypp
 * Returns: uint32_t word
 * Expectations/errors: comp not null
 */
uint32_t *convert_compressed_to_word(Compressed_struct comp)
{
    assert(comp != NULL);

    uint64_t bit_a = (int) ((comp->a) * 63);
    uint64_t bit_b = (int) ((comp->b) * 103);
    uint64_t bit_c = (int) ((comp->c) * 103);
    uint64_t bit_d = (int) ((comp->d) * 103);

    /*declare final word*/
    uint32_t *word = malloc(sizeof(uint32_t));


    /*bitpack value a*/
    assert(Bitpack_fitsu(bit_a, 6));
    *word = Bitpack_newu(*word, 6, 26, bit_a);
    

    /*bitpack value b*/
    assert(Bitpack_fitss(bit_b, 6));
    *word = Bitpack_news(*word, 6, 20, bit_b);
    

    /*bitpack value c*/
    assert(Bitpack_fitss(bit_c, 6));
    *word = Bitpack_news(*word, 6, 14, bit_c);

    /*bitpack value d*/
    assert(Bitpack_fitss(bit_d, 6));
    *word = Bitpack_news(*word, 6, 8, bit_d);

    /*bitpack value pb*/
    assert(Bitpack_fitsu(comp->pb_index, 4));
    *word = Bitpack_newu(*word, 4, 4, comp->pb_index);

    /*bitpack value pr*/
    assert(Bitpack_fitsu(comp->pr_index, 4));
    *word = Bitpack_newu(*word, 4, 0, comp->pr_index);
    
    return (uint32_t*) word;
}

/*
 * convert_word_to_compressed
 * Behavior: unpacks a compressed component video representation 
     from a 32 bit word using the Bitpack interface
 * Parameters: uint32_t word: the codeword to be unpacked
 * Returns: Compressed_struct (compressed component video 
     representation struct): unpacked codeword values
 * Expectations/errors: none
 */
Compressed_struct convert_word_to_compressed(uint32_t *word)
{
    Compressed_struct comp;
    NEW(comp);

    comp->a = (float) Bitpack_getu(*word, 6, 26) / 63;
    comp->b = (float) Bitpack_gets(*word, 6, 20) / 103;
    comp->c = (float) Bitpack_gets(*word, 6, 14) / 103;
    comp->d = (float) Bitpack_gets(*word, 5, 8) / 103;
    comp->pb_index = (unsigned) Bitpack_getu(*word, 4, 4);
    comp->pr_index = (unsigned) Bitpack_getu(*word, 4, 0);
    return comp;
}

/*
 * compressed_to_word_apply
 * Behavior: apply function. calls convert_compressed_to_word on the
        given elem and puts it into an A2 of words
 * Parameters: 
    int i: column of A2
    int j: row of A2
    A2 compressed_A2: A2 containing structs of the values to be packed
    void *elem: the current Compressed_struct
    void *word_A2: the A2 that will store the codewords
 * Returns: none
 * Expectations/errors: elem and word_A2 should not be null
 */
void compressed_to_word_apply(int i, int j, A2 compressed_A2, void *elem, 
                                                            void *word_A2)
{
    assert(elem != NULL);
    assert(word_A2 != NULL);
    (void) compressed_A2;

    uint32_t *word = convert_compressed_to_word(elem);

    *(uint32_t*) uarray2_methods_plain->at(word_A2, i, j) = *word;

    FREE(word);
}

/*
 * word_to_compressed_apply
 * Behavior: apply function. calls convert_word_to_compressed on the
        given elem and puts it into an A2 of compressed values
 * Parameters: 
    int i: column of word_A2
    int j: row of word_A2
    A2 word_A2: A2 containing the codewords to be unpacked
    void *elem: the current codeword
    void *compressed_A2: the A2 that will contain the unpacked codewords
 * Returns: none
 * Expectations/errors: elem and compressed_A2 should not be null
 */
void word_to_compressed_apply(int i, int j, A2 word_A2, void *elem, 
                                void *compressed_A2)
{
    assert(elem != NULL);
    assert(compressed_A2 != NULL);
    (void) word_A2;

    Compressed_struct comp = convert_word_to_compressed(elem);

    *(Compressed_struct) uarray2_methods_plain->at(compressed_A2, i, j) =
                                                                        *comp;

    FREE(comp);
}