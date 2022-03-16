#ifndef REGISTERS_H_INCLUDED
#define REGISTERS_H_INCLUDED


/*****************************************************************************
 *
 *                          registers.h
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the interface for the registers module. This file
 * contains the declarations for the Registers_T incomplete struct and all the
 * functions required for clients to work with the struct.
 *
 ****************************************************************************/


#include <stdint.h>

#define T Registers_T
typedef struct T *T;


/*
 * Registers_new
 * Behavior: initializes a Registers_T struct containing 0 in every index
 * Parameters:
 *      * none
 * Returns: an initialized struct Registers_T *
 * Expectations: none
 */
extern T Registers_new();


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
 */
extern void Registers_set_reg(T reg, int index, uint32_t value);


/*
 * Registers_get_reg
 * Behavior: returns reg[index]
 * Parameters:
 *      * Registers_T reg -- the Registers_T data type that stores the
                             values of the registers
 *      * int index -- the index of the registers to be accessed
 * Returns: uint32_t value at reg[index]
 * Expectations: index is between 0 and 7, inclusive; reg is not null
 */
extern uint32_t Registers_get_reg(T reg, int index);


/*
 * Registers_free
 * Behavior: frees the data from a Registers_T struct pointer and sets it to
             NULL
 * Parameters:
 *      * Registers_T *reg -- pointer to a Registers_T struct
 * Returns: none
 * Expectations: reg and *reg are not NULL
 */
extern void Registers_free(T *reg);


/*
 * Registers_print
 * Behavior: prints all of the values of reg
 * Parameters:
 *      * Registers_T reg -- the Registers_T data type that stores the
                             values of the registers
 * Returns: none
 * Expectations: reg is not null
 */
extern void Registers_print(T reg);

#undef T
#endif