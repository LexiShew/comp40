/*****************************************************************************
 *
 *                          io_instructions.c
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the implementation for our I/O module. This file contains the
 * function definitions for all the functions that deal with input and output
 * UM instructions -- namely "input" and "output".
 *
 ****************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "io_instructions.h"
#include "registers.h"


/*
 * input
 * Behavior: takes in input from stdin and stores it in the specified register
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int c -- index of r where the input value should be stored
 * Expectations/errors: c must be between 0 and 7; r cannot be null
 * Implementation: if the input character is the end of file marker, set the
 *      value to be ~0; otherwise set the value to be the input character
 */
void input(Registers_T r, int c)
{
    int in = getchar();
    if (in == EOF) {
        Registers_set_reg(r, c, ~0);
    } else {
        Registers_set_reg(r, c, in);
    }
}


/*
 * output
 * Behavior: prints the value in the specified register to stdout
 * Parameters:
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int c -- index of r containing the value to be output
 * Expectations/errors: c must be between 0 and 7; r cannot be null; r[C] is
        between 0 and 255
 * Implementation: prints the character in the specified register to stdout
 */
void output(Registers_T r, int c)
{
    uint32_t rc = Registers_get_reg(r, c);
    assert(rc <= 255);
    printf("%c", rc);
}