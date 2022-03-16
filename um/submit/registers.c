/*****************************************************************************
 *
 *                          registers.c
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the implementation for our registers module. This file contains
 * the declaration for the Registers_T struct and function definitions for all
 * the functions that are used to modify and access registers:
 *      * Registers_new
 *      * Registers_set_reg
 *      * Registers_get_reg
 *      * Registers_free
 *      * Registers_print
 *
 ****************************************************************************/


#include "registers.h"
#include <mem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define T Registers_T


/*
 * Restisters_T
 * This incomplete struct represents the CPU registers for the UM
 */
struct T {
    uint32_t *r;
};


/*
 * Registers_new
 * Behavior: initializes a Registers_T struct containing 0 in every index
 * Parameters:
 *      * none
 * Returns: an initialized struct Registers_T *
 * Expectations: none
 * Implementation: allocates memory for a new Registers_T struct, sets its
                   registers array to a calloc'ed array.
 */
T Registers_new()
{
    T registers;
    NEW(registers);
    registers->r = calloc(8, sizeof(uint32_t));
    return registers;
}


/*
 * Registers_set_reg
 * Behavior: sets reg[index] to value
 * Parameters:
 *      * Registers_T reg -- the Registers_T data type that stores the
                             values of the registers
 *      * int index -- the index of the registers to be set
 *      * uint32_t value -- the value to be put in reg[index]
 * Returns: none
 * Expectations: index is between 0 and 7, inclusive; reg is not null
 * Implementation: sets r[index] to value in reg
 */
void Registers_set_reg(T reg, int index, uint32_t value) {
    assert(reg != NULL);
    assert(index >= 0 && index < 8);
    reg->r[index] = value;
}


/*
 * Registers_get_reg
 * Behavior: returns reg[index]
 * Parameters:
 *      * Registers_T reg -- the Registers_T data type that stores the
                             values of the registers
 *      * int index -- the index of the registers to be accessed
 * Returns: uint32_t value at reg[index]
 * Expectations: index is between 0 and 7, inclusive; reg is not null
 * Implementation: returns r[index] from reg
 */
uint32_t Registers_get_reg(T reg, int index) {
    assert(reg != NULL);
    assert(index >= 0 && index < 8);
    return reg->r[index];
}


/*
 * Registers_free
 * Behavior: frees the data from a Registers_T struct pointer and sets it to
             NULL
 * Parameters:
 *      * Registers_T *reg -- pointer to a Registers_T struct
 * Returns: none
 * Expectations: reg and *reg are not NULL
 * Implementation: frees the array from reg, frees reg itself and sets reg to
 *                 NULL
 */
void Registers_free(T *reg) {
    assert(reg != NULL && *reg != NULL);
    free((*reg)->r);
    FREE(*reg);
    reg = NULL;
}


/*
 * Registers_print
 * Behavior: prints all of the values of reg
 * Parameters:
 *      * Registers_T reg -- the Registers_T data type that stores the
                             values of the registers
 * Returns: none
 * Expectations: reg is not null
 * Implementation: loops through the array from reg, prints r[i] for 0 <= i < 8
 */
void Registers_print(T reg) {
    assert(reg);

    fprintf(stderr, "%u", reg->r[0]);
    for (int i = 1; i < 8; i++) {
        fprintf(stderr, " %u", reg->r[i]);
    }
    fprintf(stderr, "\n");
}

#undef T