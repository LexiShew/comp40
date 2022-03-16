/*****************************************************************************
 *
 *                          math_instructions.c
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the implementation for our math instructions module. This file
 * contains the function defintions for all functions used for UM instructions
 * that (mostly) relate to arithmetic operations or basic loading of values:
 *      * load_val
 *      * add
 *      * multiply
 *      * divide
 *      * NAND
 *      * conditional move
 *
 ****************************************************************************/


#include <stdint.h>
#include "math_instructions.h"
#include "registers.h"

/*
 * cond_move
 * Behavior: if the value in r[C] isn't zero, store the value in r[B] into r[A]
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of the register that will store the result
 *      * int b -- index of the register containing the first comparison value
 *      * int c -- index of the register containing the second comparison value
 * Expectations/errors: a, b, and c are between 0 and 7, r is not null
 * Implementation: if r[C] is zero, don't change anything, otherwise set r[A]
 *      to be the value in r[B]
 */
void cond_move(Registers_T r, int a, int b, int c)
{
    uint32_t rb = Registers_get_reg(r, b);
    uint32_t rc = Registers_get_reg(r, c);

    if (rc != 0) {
        Registers_set_reg(r, a, rb);
    }
}


/*
 * add
 * Behavior: stores the sum of the values r[B] and r[C] in r[A], mod 2^32
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of register that will store the sum
 *      * int b -- index of register containing the first value
 *      * int c -- index of register containing the second value
 * Expectations/errors: a, b, and c are between 0 and 7, r is not null
 * Implementation: r[A] gets the sum of r[B] and r[C]
 */
void add(Registers_T r, int a, int b, int c)
{
    uint32_t rb = Registers_get_reg(r, b);
    uint32_t rc = Registers_get_reg(r, c);
    Registers_set_reg(r, a, rb + rc);
}


/*
 * mult
 * Behavior: stores the product of the values r[B] and r[C] in r[A], mod 2^32
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of register that will store the product
 *      * int b -- index of register containing the first value
 *      * int c -- index of register containing the second value
 * Expectations/errors: a, b, and c are between 0 and 7, r is not null
 * Implementation: r[A] gets the product of r[B] and r[C]
 */
void mult(Registers_T r, int a, int b, int c)
{
    uint32_t rb = Registers_get_reg(r, b);
    uint32_t rc = Registers_get_reg(r, c);
    Registers_set_reg(r, a, rb * rc);
}


/*
 * divide
 * Behavior: stores the quotient of the values r[B] and r[C] in r[A], mod 2^32
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of register that will store the quotient
 *      * int b -- index of register containing the first value
 *      * int c -- index of register containing the second value
 * Expectations/errors: a, b, and c are between 0 and 7, r is not null; r[C] is
 *      not 0
* Implementation: r[A] gets the quotient of r[B] and r[C]
 */
void divide(Registers_T r, int a, int b, int c)
{
    uint32_t rb = Registers_get_reg(r, b);
    uint32_t rc = Registers_get_reg(r, c);
    Registers_set_reg(r, a, rb / rc);
}


/*
 * nand
 * Behavior: stores the bitwise not-and of the values r[B] and r[C] in r[A]
 *      (i.e. r[A] = not(r[A] and r[C])
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of register that will store the result
 *      * int b -- index of register containing the first value
 *      * int c -- index of register containing the second value
 * Expectations/errors: a, b, and c are between 0 and 7, r is not null
 * Implementation: r[A] gets the notted and of r[B] and r[C]
 */
void nand(Registers_T r, int a, int b, int c)
{
    uint32_t rb = Registers_get_reg(r, b);
    uint32_t rc = Registers_get_reg(r, c);
    Registers_set_reg(r, a, ~(rb & rc));
}


/*
 * load_val
 * Behavior: stores the inputted value into register A
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of register that will store the sum
 *      * int val -- the value that's to be stored in r[A]
 * Expectations/errors: a is between 0 and 7, r is not null, val has max 25
 *      bits
 * Implementation: r[A] gets the value inputted
 */
void load_val(Registers_T r, int a, int val)
{
    Registers_set_reg(r, a, val);
}
