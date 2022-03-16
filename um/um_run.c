/*****************************************************************************
 *
 *                                  um_run.c
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the implementation for the um_run sub-driver file, which
 * contains the one function, um_run, which handles unpacking and running the
 * instructions of the program, along with the helper function unpack_word and
 * its helper functions unpack_standard_word and unpack_load_val_word.
 *
 ****************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <seq.h>
#include <list.h>
#include <stdbool.h>
#include <bitpack.h>
#include <assert.h>
#include "um_run.h"
#include "mem_instructions.h"
#include "math_instructions.h"
#include "io_instructions.h"
#include "registers.h"


typedef uint32_t Um_instruction;
typedef enum Um_opcode {
        COND_MOV = 0, SEG_LOAD, SEG_STORE, ADD, MULT, DIV,
        NAND, HALT, MAP, UNMAP, OUTPUT, INPUT, LOAD_PROGRAM, LOAD_VAL
} Um_opcode;

void unpack_word(uint32_t word, Um_opcode *op,
                 int *ra, int *rb, int *rc, int *val);
void unpack_standard_word(uint32_t word, int *ra, int *rb, int *rc);
void unpack_load_val_word(uint32_t word, int *ra, int *val);
const int WORD_SIZE = 32;

/*
 * um_run
 * Behavior: executes the instructions found in the m[0] array
 * Parameters: uint32_t *m0 -- pointer to the first element of the m[0] array
 * Expectations/errors: m0 must end with a halt instruction, therefore also
 *                      can't be empty
 * Implementation: Initializes Registers_T, Memory_T and List_T recycle list,
                   loops through instructions, uses unpack_word to unpack each
                   instruction, calls respective instruction functions.
 */
void um_run(uint32_t *m0)
{

    /* registers */
    Registers_T r = Registers_new();

    /* memory */
    int hint = 10;
    Memory_T mem = Memory_new(hint);
    Memory_map_segment(mem, 0, m0);

    int program_counter = 0;

    List_T recycle_list = List_list(NULL);


    bool keep_running = true;
    Um_opcode op = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int val = 0;

    while (keep_running) {
        unpack_word(Memory_get_word(mem, 0, program_counter),
                                    &op, &a, &b, &c, &val);
        program_counter++;
        switch (op) {
            case COND_MOV:
                cond_move(r, a, b, c);
                break;

            case SEG_LOAD:
                seg_load(mem, r, a, b, c);
                break;

            case SEG_STORE:
                seg_store(mem, r, a, b, c);
                break;

            case ADD:
                add(r, a, b, c);
                break;

            case MULT:
                mult(r, a, b, c);
                break;

            case DIV:
                divide(r, a, b, c);
                break;

            case NAND:
                nand(r, a, b, c);
                break;

            case HALT:
                keep_running = false;
                break;

            case MAP:
                map(mem, &recycle_list, r, b, c);
                break;

            case UNMAP:
                unmap(mem, &recycle_list, r, c);
                break;

            case OUTPUT:
                output(r, c);
                break;

            case INPUT:
                input(r, c);
                break;

            case LOAD_PROGRAM:
                load_program(mem, &program_counter, r, b, c);
                break;

            case LOAD_VAL:
                load_val(r, a, val);
                break;

            default:
                fprintf(stderr, "Invalid instruction\n");
                exit(EXIT_FAILURE);
        }
    }
    Memory_free(&mem);
    List_free(&recycle_list);
    Registers_free(&r);
}

/*
 * unpack_word
 * Behavior: Unpacks a word and puts op, a, b, c, val into the respective
 *           pointers
 * Parameters:
 *      * uint32_t word -- the word being unpacked
 *      * Um_opcode *op -- the pointer to be assigned the opcode of word
 *      * int *a -- the pointer to be assigned the value a from word
 *      * int *b -- the pointer to be assigned the value b from a standard word
 *      * int *c -- the pointer to be assigned the value c from a standard word
 *      * int *val -- the pointer to be assigned the value val from a
 *                    loadval word
 * Expectations/errors: op, a, b, c, val must not be null
 * Implementation: Assigns *op to the correct opcode, calls either
 *                 unpack_standard_word or unpack_load_val_word
 */
void unpack_word(uint32_t word, Um_opcode *op,
                 int *a, int *b, int *c, int *val) {
    *op = Bitpack_getu(word, 4, WORD_SIZE - 4);

    if (*op == LOAD_VAL) {
        unpack_load_val_word(word, a, val);
    } else {
        unpack_standard_word(word, a, b, c);
    }
}

/*
 * unpack_standard_word
 * Behavior: Unpacks a standard word and puts a, b, c into the respective
 *           pointers
 * Parameters:
 *      * uint32_t word -- the word being unpacked
 *      * int *a -- the pointer to be assigned the value a from word
 *      * int *b -- the pointer to be assigned the value b from word
 *      * int *c -- the pointer to be assigned the value c from word
 * Expectations/errors: a, b, c, word should be a standard word (not a loadval)
 * Implementation: Assigns *a, *b, *c using the bitpack library
 */
void unpack_standard_word(uint32_t word, int *a, int *b, int *c)
{
    *c = Bitpack_getu(word, 3, 0);
    *b = Bitpack_getu(word, 3, 3);
    *a = Bitpack_getu(word, 3, 6);
}

/*
 * unpack_load_val_word
 * Behavior: Unpacks a word and puts a, val into the respective pointers
 * Parameters:
 *      * uint32_t word -- the word being unpacked
 *      * int *a -- the pointer to be assigned the value a from word
 *      * int *val -- the pointer to be assigned the value val from word
 * Expectations/errors: a, val must not be null
 * Implementation: Assigns *a and *val using the bitpack library
 */
void unpack_load_val_word(uint32_t word, int *a, int *val)
{
    *a = Bitpack_getu(word, 3, WORD_SIZE - 7);
    *val = Bitpack_getu(word, 25, 0);
}