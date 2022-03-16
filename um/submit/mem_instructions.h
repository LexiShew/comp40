#ifndef MEM_INSTRUCTIONS_H_INCLUDED
#define MEM_INSTRUCTIONS_H_INCLUDED


/*****************************************************************************
 *
 *                          mem_instructions.h
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the interface for the mem_instructions module. This file
 * contains the declarations for all the memory-related functions that the
 * instructions of the UM can can execute.
 *
 ****************************************************************************/


#include <list.h>
#include <stdint.h>
#include "memory.h"
#include "registers.h"

/*
 * seg_load
 * Behavior: loads the value at m[r[A]][r[B]] into register A
 * Parameters:
 *      * Memory_T mem -- the Memory_T data type that stores the UM memory
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of the register that will store the word
 *      * int b -- index of the register that contains the mem segment index
 *      * int c -- index of the register that contains the mem word index
 * Expectations: a, b, c, are between 0 and 7; r and mem are not null
 */
extern void seg_load(Memory_T mem, Registers_T r, int a, int b, int c);


/*
 * seg_store
 * Behavior: stores the value in r[C] into the word at m[r[A]][r[B]]
 * Parameters:
 *      * Memory_T mem -- the Memory_T data type that stores the UM memory
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of the register that contains the word to be stored
 *      * int b -- index of the register that contains the mem segment index
 *      * int c -- index of the register that contains the mem word index
 * Expectations: a, b, c, are between 0 and 7; r and mem are not null
 */
extern void seg_store(Memory_T mem, Registers_T r, int a, int b, int c);


/*
 * map
 * Behavior: creates a new segment at m[r[B]] of an inputted size r[C]
 * Parameters:
 *      * Memory_T mem -- the Memory_T data type that stores the UM memory
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int b -- index of the register containing the info of where the new
 *              segment should be placed in mem
 *      * int c -- index of the register containing the length of the new
 *              segment to be mapped
 * Expectations/errors: b and c are between 0 and 7, mem, rec_list, and r are
 *      not null
 */
extern void map(Memory_T mem, List_T *rec_list, Registers_T r, int b, int c);


/*
 * unmap
 * Behavior: removes and frees the segment at m[r[C]]
 * Parameters:
 *      * Memory_T mem -- the Memory_T data type that stores the UM memory
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * List_T *rec_list -- address of the Hanson List that stores the
 *              indices in memory that have been unmapped
 *      * int c -- index of the register containing the index of memory that's
 *              to be unmapped
 * Expectations: c is between 0 and 7; r, rec_list, and mem are not null; the
 *      segment being upmapped has been previously mapped and is not segment 0
 */
extern void unmap(Memory_T mem, List_T *rec_list, Registers_T r, int c);


/*
 * load_program
 * Behavior: change the instructions to be executed to a different set of words
 * Parameters:
 *      * Memory_T mem -- the Memory_T data type that stores the UM memory
 *      * int *program_counter -- address of the the variable that stores the
 *          index of the current instruction to be run
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int b -- index of register containing the mem index which contains
 *              the segment that's to be loaded into r[0]
 *      * int c -- index of register containing index of the word for the
 *              that the program_counter should point to
 * Expectations: b and c are between 0 and 7; r, mem, and program_counter
 *          are not null; r[C] is within the length of the segment
 */
extern void load_program(Memory_T mem, int *program_counter,
                         Registers_T r, int b, int c);

#endif