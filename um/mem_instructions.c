/*****************************************************************************
 *
 *                          mem_instructions.c
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the implementation for our memory instructions module. This
 * file contains the function definitions for all the functions that are used
 * by UM memory-related instructions:
 *      * segmented load
 *      * segmented store
 *      * map
 *      * unmap
 *      * load program
 *
 ****************************************************************************/


#include <stdint.h>
#include <list.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <mem.h>
#include "mem_instructions.h"
#include "memory.h"
#include "registers.h"


/*
 * seg_load
 * Behavior: loads the value at mem[r[A]][r[B]] into register A
 * Parameters:
 *      * Memory_T mem -- the Memory_T data type that stores the UM memory
 *      * Registers_T r -- the registers that the UM simulated CPU uses
 *      * int a -- index of the register that will store the word
 *      * int b -- index of the register that contains the mem segment index
 *      * int c -- index of the register that contains the mem word index
 * Implementation: accesses the word at mem(r[B], r[C]) and sets r[A] to that
 *      word
 */
void seg_load(Memory_T mem, Registers_T r, int a, int b, int c)
{
    uint32_t rb = Registers_get_reg(r, b);
    uint32_t rc = Registers_get_reg(r, c);
    Registers_set_reg(r, a, Memory_get_word(mem, rb, rc));
}


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
 * Implementation: sets the value at r[A] to be the value at mem(r{b], r[C])
 */
void seg_store(Memory_T mem, Registers_T r, int a, int b, int c)
{
    uint32_t ra = Registers_get_reg(r, a);
    uint32_t rb = Registers_get_reg(r, b);
    uint32_t rc = Registers_get_reg(r, c);
    Memory_set_word(mem, ra, rb, rc);
}


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
 * Implementation: if there are no memory indicies that have been unmapped and
 *      are now empty, map the new segment to the end of memory; if there are
 *      memory indices that need to be remapped, map to those first, in LIFO
 *      order
 */
void map(Memory_T mem, List_T *rec_list, Registers_T r, int b, int c)
{
    uint32_t rc = Registers_get_reg(r, c);
    if (*rec_list == NULL) {
        Registers_set_reg(r, b, Memory_map_new_segment(mem, -1, rc));
    } else {
        void *rec_index;
        *rec_list = List_pop(*rec_list, &rec_index);
        int real_rec_index = (int)(uintptr_t) rec_index;
        Registers_set_reg(r, b,
                          Memory_map_new_segment(mem, real_rec_index, rc));
    }
}


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
 * Implementation: add the index of the unmapped segment to the recycle list,
 *      free the memory assocated with the unmapped segment
 */
void unmap(Memory_T mem, List_T *rec_list, Registers_T r, int c)
{
    uint32_t rc = Registers_get_reg(r, c);
    assert(rc != 0);
    assert(rec_list != NULL);

    *rec_list = List_push(*rec_list, (void*)(uintptr_t) rc);

    Memory_unmap_segment(mem, rc);
}


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
 * Implementation: if r[B] is 0, just shift the program counter to r[C].
 *          Otherwise, unmap m[0], copy m[r[C]], load it into m[0], and set
 *          the program counter
 */
void load_program(Memory_T mem, int *program_counter, Registers_T r, int b,
                                                                     int c)
{
    uint32_t rb = Registers_get_reg(r, b);
    uint32_t rc = Registers_get_reg(r, c);
    if (rb != 0) {
        Memory_unmap_segment(mem, 0);

        uint32_t *segment = Memory_get_segment(mem, rb);

        assert(segment != NULL);
        int length = Memory_segment_length(mem, rb);
        Memory_map_new_segment(mem, 0, length);
        for (int i = -1; i < length; i++) {
            Memory_set_word(mem, 0, i, Memory_get_word(mem, rb, i));
        }
        assert((int) rc < length);
    }
    else {
        assert((int) rc < Memory_segment_length(mem, 0));
    }
    *program_counter = rc;
}