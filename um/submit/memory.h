#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED


/*****************************************************************************
 *
 *                              memory.h
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the interface for the memory module. It contains the
 * declarations for all the structs and functions used to create, access, and
 * alter the UM memory.
 *
 ****************************************************************************/


#include <stdint.h>

#define T Memory_T
typedef struct T *T;


/*
 * Memory_new
 * Behavior: creates a new Memory_T instance
 * Parameters:
 *      * int hint -- a hint of how many segments the Memory_T might contain
 * Return:
 *      * pointer to the created Memory_T object
 * Expectations: hint is greater than 0
 */
extern T Memory_new(int hint);


/*
 * Memory_length
 * Behavior: returns the length of the inputted Memory_T
 * Parameters:
 *      * Memory_T mem -- the Memory_T whose length is being accessed
 * Return: int -- the length of the Memory_T object
 * Expectations: mem is not null
 */
extern int Memory_length(T mem);


/*
 * Memory_unmap_segment
 * Behavior: unmaps the segment at a given index
 * Parameters:
 *      * Memory_T mem -- the Memory_T being altered
 *      * int index -- the index of the segment within mem to be unmapped
 * Expectations: mem is not null, index is between 0 and length - 1
 */
extern void Memory_unmap_segment(T mem, int index);


/*
 * Memory_map_segment
 * Behavior: maps a segment to a given index in memory
 * Parameters:
 *      * Memory_T mem -- the Memory_T being altered
 *      * int index -- the index where the segment should be mapped
 *      * uint32_t *segment -- the segment that's to be mapped
 * Return: int -- the index in memory that the segment is mapped to
 * Expectations: mem is not null, index is greater than or equal to 0
 */
extern int Memory_map_segment(T mem, int index, uint32_t *segment);


/*
 * Memory_map_new_segment
 * Behavior: creates a new segment and maps it to a given index in memory
 * Parameters:
 *      * Memory_T mem -- the Memory_T being altered
 *      * int index -- the index where the segment should be mapped
 *      * int seg_length -- the legnth of the new segment
 * Return: int -- the index in memory that the segment is mapped to
 * Expectations: mem is not null, index is greater than or equal to zero,
 *      seg_length is greater than or equal to zero
 */
extern int Memory_map_new_segment(T mem, int index, int seg_length);


/*
 * Memory_get_segment
 * Behavior: returns the segment at a given index in memory
 * Parameters:
 *      * Memory_T mem -- the Memory_T being accessed
 *      * int index -- the index of the segment to be returned
 * Return: uint32_t* -- pointer to the segment at index in mem
 * Expectations: mem is not null, index is between 0 and length - 1
 */
extern uint32_t *Memory_get_segment(T mem, int index);


/*
 * Memory_segment_length
 * Behavior: returns the length of the segment at the given index in mem
 * Parameters:
 *      * Memory_T mem -- the Memory_T being accessed
 *      * int index -- the index of the segment whose length is being accessed
 * Return: int -- the length of the segment
 * Expectations: mem is not null, index is between 0 and length - 1
 */
extern int Memory_segment_length(T mem, int index);


/*
 * Memory_set_word
 * Behavior: sets the word at mem(segment_index, word_index) to the inputted
 *      word
 * Parameters:
 *      * Memory_T mem -- the Memory_T being altered
 *      * int segment_index -- the index in mem of the segment
 *      * int word_index -- the index in the segment where the word is to be
 *                      stored
 *      * uint32_t word -- the word that's being inputted at the given spot in
 *                      mem
 * Expectations: mem is not null, segment_index is between 0 and seg_length-1,
 *      word_length is between -1 and word_length-1
 */
extern void Memory_set_word(T mem, int segment_index, int word_index,
                                                        uint32_t word);


/*
 * Memory_get_word
 * Behavior: returns the word at mem(segment_index, word_index)
 * Parameters:
 *      * Memory_T mem -- the Memory_T being accessed
 *      * int segment_index -- the index in mem of the segment
 *      * int word_index -- the index in the segment where the word is stored
 * Expectations: mem is not null, segment_index is between 0 and seg_length-1,
 *      word_length is between -1 and word_length-1
 */
extern uint32_t Memory_get_word(T mem, int segment_index, int word_index);


/*
 * Memory_free
 * Behavior: frees the memory assocciated with the inputted Memory_T
 * Parameters:
 *      * Memory_T *mem -- the Memory_T being freed
 * Expectations: *mem and mem are not null
 */
extern void Memory_free(T *mem);


/*
 * Memory_print
 * Behavior: prints the contents of the inputted Memory_T
 * Parameters:
 *      * Memory_T mem -- the Memory_T being accessed
 * Expectations: mem is not null
 */
extern void Memory_print(T mem);


#undef T
#endif