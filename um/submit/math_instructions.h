#ifndef MATH_INSTRUCTIONS_H_INCLUDED
#define MATH_INSTRUCTIONS_H_INCLUDED


/*****************************************************************************
 *
 *                          math_instructions.h
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the interface for the math instructions module. This file
 * contains the function declarations for all the fucntions that deal with
 * arithmetic operations (add, multiply, and divide), bitwise NAND, conditional
 * move, and basic loading of values.
 *
 ****************************************************************************/


#include <stdint.h>
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
 */
extern void cond_move(Registers_T, int a, int b, int c);


/*
 * add
 * Behavior: stores the sum of the values r[B] and r[C] in r[A], mod 2^32
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of register that will store the sum
 *      * int b -- index of register containing the first value
 *      * int c -- index of register containing the second value
 * Expectations/errors: a, b, and c are between 0 and 7, r is not null
 */
extern void add(Registers_T r, int a, int b, int c);


/*
 * mult
 * Behavior: stores the product of the values r[B] and r[C] in r[A], mod 2^32
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of register that will store the product
 *      * int b -- index of register containing the first value
 *      * int c -- index of register containing the second value
 * Expectations/errors: a, b, and c are between 0 and 7, r is not null
 */
extern void mult(Registers_T r, int a, int b, int c);


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
 */
extern void divide(Registers_T r, int a, int b, int c);


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
 */
extern void nand(Registers_T r, int a, int b, int c);


/*
 * load_val
 * Behavior: stores the inputted value into register A
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of register that will store the sum
 *      * int val -- the value that's to be stored in r[A]
 * Expectations/errors: a is between 0 and 7, r is not null, val has max 25
 *      bits
 */
extern void load_val(Registers_T r, int a, int val);

#endif