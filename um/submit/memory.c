/*****************************************************************************
 *
 *                              memory.c
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the implementation for our Memory module. This file contains
 * the function and struct defintions for the Memory_T data type. The public
 * functions can be used to get segments, words, lengths of the memory and
 * segments, map, unmap, create new segments, free memory, and print the
 * contents of memory.
 *
 ****************************************************************************/


#include <seq.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <mem.h>
#include <assert.h>
#include "memory.h"

#define T Memory_T


/*
 * Memory_T
 * This incomplete struct represents the memory of the UM
 */
struct T {
    Seq_T seq;
};


/*
 * Memory_new
 * Behavior: creates a new Memory_T instance
 * Parameters:
 *      * int hint -- a hint of how many segments the Memory_T might contain
 * Return:
 *      * pointer to the created Memory_T object
 * Expectations: hint is greater than 0
 * Implementation: creates a Hanson Sequence and sets that to seq within
 *      Memory_T object
 */
T Memory_new(int hint)
{
    T mem;
    NEW(mem);
    mem->seq = Seq_new(hint);
    return mem;
}


/*
 * Memory_length
 * Behavior: returns the length of the inputted Memory_T
 * Parameters:
 *      * Memory_T mem -- the Memory_T whose length is being accessed
 * Return: int -- the length of the Memory_T object
 * Expectations: mem is not null
 * Implementation: returns length of underlying sequence
 */
int Memory_length(T mem)
{
    assert(mem != NULL);
    return Seq_length(mem->seq);
}


/*
 * Memory_unmap_segment
 * Behavior: unmaps the segment at a given index
 * Parameters:
 *      * Memory_T mem -- the Memory_T being altered
 *      * int index -- the index of the segment within mem to be unmapped
 * Expectations: mem is not null, index is between 0 and length - 1
 * Implementation: frees segment if it's not already null, sets mem(index) to
 *      null
 */
void Memory_unmap_segment(T mem, int index)
{
    assert(mem != NULL);
    assert(index >= 0 && index < Memory_length(mem));
    uint32_t *segment = Seq_put(mem->seq, index, NULL);
    if (segment != NULL) {
        free(segment);
    }
}


/*
 * Memory_map_segment
 * Behavior: maps a segment to a given index in memory
 * Parameters:
 *      * Memory_T mem -- the Memory_T being altered
 *      * int index -- the index where the segment should be mapped.
 *              To append to end, set index to -1
 *      * uint32_t *segment -- the segment that's to be mapped
 * Return: int -- the index in memory that the segment is mapped to
 * Expectations: mem is not null, index is greater than or equal to 0
 * Implementation: if index is -1, add to end; if adding at an index greater
 *      than length, fill mem with nulls until reaching that index; if another
 *      segment is already mapped to that index, unmap it; insert segment at
 *      given index
 */
int Memory_map_segment(T mem, int index, uint32_t *segment)
{
    assert(mem != NULL);
    if (index == -1) {
        Seq_addhi(mem->seq, segment);
        return Memory_length(mem) - 1;
    }
    else {
        while (Memory_length(mem) - 1 < index) {
            Seq_addhi(mem->seq, NULL);
        }
        /* free memory if you're mapping over something */
        if (Memory_get_segment(mem, index) != NULL) {
            Memory_unmap_segment(mem, index);
        }
        Seq_put(mem->seq, index, segment);
        return index;
    }
}


/*
 * Memory_map_new_segment
 * Behavior: creates a new segment and maps it to a given index in memory
 * Parameters:
 *      * Memory_T mem -- the Memory_T being altered
 *      * int index -- the index where the segment should be mapped
 *              To append to end, set index to -1
 *      * int seg_length -- the legnth of the new segment
 * Return: int -- the index in memory that the segment is mapped to
 * Expectations: mem is not null, index is greater than or equal to zero,
 *      seg_length is greater than or equal to zero
 * Implementation: creates a new uint32_t of size seg_length to be inserted
 *      at the given index
 */
int Memory_map_new_segment(T mem, int index, int seg_length)
{
    assert(seg_length >= 0);
    uint32_t *segment = calloc(seg_length + 1, sizeof(uint32_t));
    assert(segment != NULL);
    segment[0] = seg_length;
    return Memory_map_segment(mem, index, segment);
}


/*
 * Memory_get_segment
 * Behavior: returns the segment at a given index in memory
 * Parameters:
 *      * Memory_T mem -- the Memory_T being accessed
 *      * int index -- the index of the segment to be returned
 * Return: uint32_t* -- pointer to the segment at index in mem
 * Expectations: mem is not null, index is between 0 and length - 1
 * Implementation: return the value in the underlying sequence at index
 */
uint32_t *Memory_get_segment(T mem, int index)
{
    assert(mem != NULL);
    assert(index >= 0 && index < Memory_length(mem));
    return (uint32_t *) Seq_get(mem->seq, index);
}


/*
 * Memory_segment_length
 * Behavior: returns the length of the segment at the given index in mem
 * Parameters:
 *      * Memory_T mem -- the Memory_T being accessed
 *      * int index -- the index of the segment whose length is being accessed
 * Return: int -- the length of the segment
 * Expectations: mem is not null, index is between 0 and length - 1
 * Implementation: access the first element of the segment -- this stores the
 *      length of the segment
 */
int Memory_segment_length(T mem, int index)
{
    assert(mem != NULL);
    assert(index >= 0 && index < Memory_length(mem));
    return (int) Memory_get_word(mem, index, -1);
}


/*
 * Memory_segment_length
 * Behavior: returns the length of the segment at the given index in mem
 * Parameters:
 *      * Memory_T mem -- the Memory_T being altered
 *      * int index -- the index of the segment whose length is being accessed
 * Return: int -- the length of the segment
 * Expectations: mem is not null, index is between 0 and length - 1
 */
void Memory_set_word(T mem, int segment_index, int word_index, uint32_t word)
{
    assert(mem != NULL);
    assert(segment_index >= 0 && segment_index < Memory_length(mem));
    assert(word_index >= -1 && 
           word_index < Memory_segment_length(mem, segment_index));
    // May be too slow, re-getting segments repeatedly
    uint32_t *segment = Memory_get_segment(mem, segment_index);
    assert(segment != NULL);
    segment[word_index + 1] = word;
}


/*
 * Memory_get_word
 * Behavior: returns the word at mem(segment_index, word_index)
 * Parameters:
 *      * Memory_T mem -- the Memory_T being accessed
 *      * int segment_index -- the index in mem of the segment
 *      * int word_index -- the index in the segment where the word is stored
 * Expectations: mem is not null, segment_index is between 0 and seg_length-1,
 *      word_length is between -1 and word_length-1
 * Implementation: returns the word at  index + 1 (since segment[0] = length
 *      of segment)
 */
uint32_t Memory_get_word(T mem, int segment_index, int word_index)
{
    assert(mem != NULL);
    assert(segment_index >= 0 && segment_index < Memory_length(mem));
    uint32_t *segment = Memory_get_segment(mem, segment_index);
    assert(segment != NULL);
    assert(word_index >= -1 && word_index < (int) segment[0]);
    // May be too slow, re-getting segments repeatedly
    return segment[word_index + 1];
}


/*
 * Memory_free
 * Behavior: frees the memory assocciated with the inputted Memory_T
 * Parameters:
 *      * Memory_T *mem -- the Memory_T being freed
 * Expectations: *mem and mem are not null
 * Implementation: unmaps every segment in mem, frees underlying Sequence, and
 *      frees the struct
 */
void Memory_free(T *mem)
{
    assert(mem != NULL && *mem != NULL);
    int length = Memory_length(*mem);
    for (int i = 0; i < length; i++) {
        Memory_unmap_segment(*mem, i);
    }
    Seq_free(&((*mem)->seq));
    FREE(*mem);
}


/*
 * Memory_print
 * Behavior: prints the contents of the inputted Memory_T
 * Parameters:
 *      * Memory_T mem -- the Memory_T being accessed
 * Expectations: mem is not null
 * Implementation: prints the length of mem and all the segments and their
 *      contents with their lengths
 */
void Memory_print(T mem)
{
    assert(mem != NULL);
    int seq_length = Memory_length(mem);
    for (int i = 0; i < seq_length; i++) {
        if (Memory_get_segment(mem, i) != NULL) {
            int seg_length = Memory_segment_length(mem, i);
            fprintf(stderr, "    m[%d] (size = %d): ", i, seg_length);
            for (int j = 0; j < seg_length; j++) {
                fprintf(stderr, "%x ", Memory_get_word(mem, i, j));
            }
            fprintf(stderr, "\n");
        } else {
            fprintf(stderr, "    m[%d]: NULL\n", i);
        }
    }
    fprintf(stderr, "\n");
}

#undef T