/**************************************************************
 *
 *                     bitpack.c
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * Implementation for bitpacking and retriving bits from words.
 * Function implementations include:
    shift_left
    shift_right
    shift_right_signed
    Bitpack_fitsu
    Bitpack_fitss
    Bitpack_getu
    Bitpack_gets
    Bitpack_newu
    Bitpack_news
 *
 **************************************************************/

#include "assert.h"
#include <stdio.h>
#include <stdint.h>
#include "file-ppm.h"
#include "a2methods.h"
#include <mem.h>
#include "bitpack.h"
#include "except.h"
#include <inttypes.h> /* for printing uint */

Except_T Bitpack_Overflow = { "Overflow packing bits" };

const unsigned MAX_BITS = 64;


/* HELPER FUNCTIONS */
uint64_t shift_left(uint64_t word, uint64_t offset);
uint64_t shift_right(uint64_t word, uint64_t offset);
int64_t shift_right_signed(int64_t word, uint64_t offset);

/*
 * shift_left
 * Behavior: shifts a given 64 bit word to the left by a given offset
 * Parameters: 
    uint64_t word - word to be shifted
    uint64_t offset
 * Returns: uint64_t - shifted word
 * Expectations/errors: offset <= 64
 */
uint64_t shift_left(uint64_t word, uint64_t offset) {
    assert(offset <= MAX_BITS);
    if (offset < MAX_BITS) {
        return (word << offset);
    }
    else {
        return 0;
    }
}

/*
 * 
 * Behavior: shifts a given 64 bit word to the right by a given offset
 * Parameters: 
    uint64_t word - word to be shifted
    uint64_t offset
 * Returns: uint64_t - shifted word
 * Expectations/errors: offset <= 64
 */
uint64_t shift_right(uint64_t word, uint64_t offset) {
    assert(offset <= MAX_BITS);
    if (offset < MAX_BITS) {
        word = (word >> offset);
    }
    else {
        word = 0;
    }
    return word;
}

/*
 * 
 * Behavior: shifts a given 64 bit word to the right by a given offset
    and takes sign into account by back filling with 1s if the word is
    negative and is being shifted by more than 63
 * Parameters: 
    uint64_t word - word to be shifted
    uint64_t offset
 * Returns: uint64_t - shifted word
 * Expectations/errors: offset <= 64
 */
int64_t shift_right_signed(int64_t word, uint64_t offset) {
    assert(offset <= MAX_BITS);
    /*If word is negative and shifting by more than 63, fill with 1s*/
    if (offset < MAX_BITS) {
        word = (word >> offset);
    }
    else if (word < 0) {
        word = ~0;
    }
    else {
        word = 0;       
    }
    return word;
}

/*Width-test functions*/
/*
 * Bitpack_fitsu
 * Behavior: checks if an argument 'n' can be represented in 'width' bits
 * Parameters: 
    unsigned 64 bit integer n
    unsigned width
 * Returns: boolean true if 'n' can be represented in 'width' bits.
    otherwise, boolean false
 * Expectations/errors: 
    width <= 64
 */
bool Bitpack_fitsu(uint64_t n, unsigned width)
{
    assert(width <= MAX_BITS);
    if (width == 0 && (n != 0)) {
        return false;
    }

    /*since n is 64 bits, if width is 64 or greater, n must fit*/
    if (width >= MAX_BITS) {
        return true;
    }

    /*if n is shifted by width bits, it should be 0, 
    otherwise its too big to be represented by width bits*/
    return shift_right(n, width) == 0;
}

/*
 * Bitpack_fitss
 * Behavior: checks if an argument 'n' can be represented in 'width' bits
 * Parameters: 
    signed 64 bit integer n
    unsigned width
 * Returns: boolean true if 'n' can be represented in 'width' bits.
    Otherwise, boolean false
 * Expectations/errors: 
    width <= 64
 */
bool Bitpack_fitss(int64_t n, unsigned width)
{
    assert(width <= MAX_BITS);

    if (width == 0 && (n != 0)) {
        return false;
    }

    int64_t highest_val = shift_right((uint64_t) ~0, (MAX_BITS - width) + 1); 
    int64_t lowest_val = shift_left(~0, width - 1);

    return (n <= highest_val && n >= lowest_val);
}

/*Field-extraction functions*/
/*
 * Bitpack_getu
 * Behavior: extracts a unsigned value from a word given width of field
            and location of field's least significant bit
 * Parameters: 
    unsigned 64 bit integer word
    unsigned width of field
    unsigned least significant bit
 * Returns: unsigned 64 bit value from given word
 * Expectations/errors: 
    0 <= width <= 64
    width + lsb <= 64
 */
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
    assert(width <= MAX_BITS);
    assert(width + lsb <= MAX_BITS);

    if (width == 0) {
        return (uint64_t) 0;
    }

    word = shift_left(word, MAX_BITS - (width + lsb));
    word = shift_right(word, MAX_BITS - width);
    return word;
}

/*
 * Bitpack_gets
 * Behavior: extracts a signed value from a word given width of field
            and location of field's least significant bit
 * Parameters: 
    signed 64 bit integer word
    unsigned width of field
    unsigned least significant bit
 * Returns: signed 64 bit value from given word
 * Expectations/errors: 
      0 <= width <= 64
      width + lsb <= 64
 */
int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb)
{
    assert(width <= MAX_BITS);
    assert(width + lsb <= MAX_BITS);

    if (width == 0) {
        return (uint64_t) 0;
    }

    word = shift_left(word, MAX_BITS - (width + lsb));
    word = shift_right_signed(word, MAX_BITS - width);
    return (int64_t) word;
}

/*Field-update functions*/
/*
 * Bitpack_newu
 * Behavior: return a new word identical to the original word, 
      except that the field of width 'width' with least significant bit at
      'lsb' will have been replaced by a width-bit representation of value
 * Parameters: 
      unsigned 64 bit int word
      unsigned width of section of word to be replaced
      unsigned lsb, location of word to be replaced
      unsigned 64 bit int value to replace said section of word
 * Returns: unsigned 64 bit int word with replaced value
 * Expectations/errors: 
      0 <= width <= 64
      width + lsb <= 64
 */
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, 
                    uint64_t value)
{
    assert(width <= MAX_BITS);
    assert(width + lsb <= MAX_BITS);

    if (Bitpack_fitsu(value, width) == false) {
        RAISE(Bitpack_Overflow);
    }

    uint64_t mask_h = ~0;
    mask_h = shift_left(mask_h, lsb+width);
    uint64_t mask_l = ~0;
    mask_l = shift_right(mask_l, MAX_BITS - lsb);
    uint64_t final_mask = (mask_h | mask_l);

    word =  (word & final_mask); /*zero out the present value there*/
    return word | shift_left(value, lsb); 
}

/*
 * Bitpack_news
 * Behavior: return a new word identical to the original word, 
        except that the field of width 'width' with least significant bit at
        'lsb' will have been replaced by a width-bit representation of value
 * Parameters: 
        unsigned 64 bit int word
        unsigned width of section of word to be replaced
        unsigned lsb, location of word to be replaced
        signed 64 bit int value to replace said section of word
 * Returns: unsigned 64 bit int word with replaced value
 * Expectations/errors: 
        0 <= width <= 64
        width + lsb <= 64
 */
uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb, 
                        int64_t value)
{

    assert(width <= MAX_BITS);
    assert(width + lsb <= MAX_BITS);

    if (Bitpack_fitss(value, width) == false) {
        RAISE(Bitpack_Overflow);
    }
    uint64_t mask_h = ~0;
    mask_h = shift_left(mask_h, lsb + width);
    uint64_t mask_l = ~0;
    mask_l = shift_right(mask_l, MAX_BITS - lsb);
    uint64_t final_mask = (mask_h | mask_l);


    word = (word & final_mask); /*zero out the present uvalue there*/

    uint64_t shifted_value = shift_left((uint64_t) value, (MAX_BITS - width));
    shifted_value = shift_right(shifted_value, (MAX_BITS - lsb - width));

    word = word | shifted_value;

    return word;
}