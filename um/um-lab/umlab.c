/*
 * umlab.c
 *
 * Functions to generate UM unit tests. Once complete, this module
 * should be augmented and then linked against umlabwrite.c to produce
 * a unit test writing program.
 *  
 * A unit test is a stream of UM instructions, represented as a Hanson
 * Seq_T of 32-bit words adhering to the UM's instruction format.  
 * 
 * Any additional functions and unit tests written for the lab go
 * here. 
 *  
 */


#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <seq.h>
#include <bitpack.h>


typedef uint32_t Um_instruction;
typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;


/* Functions that return the two instruction types */

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc)
{
        int MAX_SIZE = 32;
        Um_instruction word = 0;
        word = Bitpack_newu(word, 4, MAX_SIZE - 4, op);
        word = Bitpack_newu(word, 3, 0, rc);
        word = Bitpack_newu(word, 3, 3, rb);
        word = Bitpack_newu(word, 3, 6, ra);
        return word;
}


Um_instruction loadval(unsigned ra, unsigned val)
{
        int MAX_SIZE = 32;
        Um_instruction word = 0;
        word = Bitpack_newu(word, 4, MAX_SIZE - 4, LV);
        word = Bitpack_newu(word, 3, MAX_SIZE - 7, ra);
        word = Bitpack_newu(word, 25, 0, val);
        return word;
}


/* Wrapper functions for each of the instructions */

static inline Um_instruction halt(void) 
{
        return three_register(HALT, 0, 0, 0);
}

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;

static inline Um_instruction add(Um_register a, Um_register b, Um_register c) 
{
        return three_register(ADD, a, b, c);
}

static inline Um_instruction mul(Um_register a, Um_register b, Um_register c) 
{
        return three_register(MUL, a, b, c);
}


static inline Um_instruction divide(Um_register a, Um_register b, Um_register c) 
{
        return three_register(DIV, a, b, c);
}

static inline Um_instruction nand(Um_register a, Um_register b, Um_register c) 
{
        return three_register(NAND, a, b, c);
}

static inline Um_instruction input(Um_register c) 
{
        return three_register(IN, 0, 0, c);
}

Um_instruction output(Um_register c)
{
        return three_register(OUT, 0, 0, c);
}

Um_instruction map(Um_register b, Um_register c)
{
        return three_register(ACTIVATE, 0, b, c);
}

Um_instruction unmap(Um_register c)
{
        return three_register(INACTIVATE, 0, 0, c);
}

Um_instruction seg_store(Um_register a, Um_register b, Um_register c)
{
        return three_register(SSTORE, a, b, c);
}

Um_instruction seg_load(Um_register a, Um_register b, Um_register c)
{
        return three_register(SLOAD, a, b, c);
}

Um_instruction cond_move(Um_register a, Um_register b, Um_register c)
{
        return three_register(CMOV, a, b, c);
}

Um_instruction load_program(Um_register b, Um_register c)
{
        return three_register(LOADP, 0, b, c);
}

/* Functions for working with streams */

static inline void append(Seq_T stream, Um_instruction inst)
{
         // turns 32-bit int to a void ptr w/o getting mad
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t)inst);
}

const uint32_t Um_word_width = 32;

void Um_write_sequence(FILE *output, Seq_T stream)
{
        assert(output != NULL && stream != NULL);
        int stream_length = Seq_length(stream);
        for (int i = 0; i < stream_length; i++) {
                Um_instruction inst = (uintptr_t)Seq_remlo(stream);
                for (int lsb = Um_word_width - 8; lsb >= 0; lsb -= 8) {
                        fputc(Bitpack_getu(inst, 8, lsb), output);
                }
        }
}


/* Unit tests for the UM */

void build_halt_test(Seq_T stream)
{
        append(stream, halt());
}

// void build_load_val_test(Seq_T stream)
// {
//         appredn(stream, load_val()
// }


void build_verbose_halt_test(Seq_T stream)
{
        append(stream, halt());
        append(stream, loadval(r1, 'B'));
        append(stream, output(r1));
        append(stream, loadval(r1, 'a'));
        append(stream, output(r1));
        append(stream, loadval(r1, 'd'));
        append(stream, output(r1));
        append(stream, loadval(r1, '!'));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
}

void build_print_six_test(Seq_T stream)
{
        append(stream, loadval(r1, 48));
        append(stream, loadval(r2, 6));
        append(stream, add(r3, r1, r2));
        append(stream, output(r3));
        append(stream, halt());
}

void build_load_extreme_test(Seq_T stream)
{
        append(stream, loadval(r0, 0));
        append(stream, loadval(r1, 12));
        append(stream, loadval(r2, 129));
        append(stream, loadval(r3, 200));
        append(stream, loadval(r4, 5));
        append(stream, loadval(r5, 255));
        append(stream, loadval(r6, 57));
        append(stream, loadval(r7, 84));
        append(stream, output(r1));
        append(stream, output(r2));
        append(stream, output(r3));
        append(stream, output(r4));
        append(stream, output(r5));
        append(stream, output(r6));
        append(stream, output(r7));
        append(stream, halt());
}

// void build_load_bad_test(Seq_T stream) // BAD
// {
//         append(stream, loadval(r2, 260));
//         append(stream, loadval(r3, 1000));
//         append(stream, output(r2));
//         append(stream, output(r3));
// }

void build_add_test(Seq_T stream)
{
        // this will print out some icky ASCII control char (5)
        append(stream, loadval(r2, 48));
        append(stream, loadval(r3, 3));
        append(stream, add(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_add_zeros_test(Seq_T stream)
{
        append(stream, loadval(r2, 0));
        append(stream, loadval(r3, 0));
        append(stream, add(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_add_zero_three_test(Seq_T stream)
{
        append(stream, loadval(r2, 0));
        append(stream, loadval(r3, 3));
        append(stream, add(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_add_three_zero_test(Seq_T stream)
{
        append(stream, loadval(r2, 3));
        append(stream, loadval(r3, 0));
        append(stream, add(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_add_15_20_test(Seq_T stream)
{
        append(stream, loadval(r2, 15));
        append(stream, loadval(r3, 20));
        append(stream, add(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_add_big_test(Seq_T stream)
{
        append(stream, loadval(r2, 1));
        uint32_t big = ~0;
        big >>= 16;
        uint32_t multiplier = 65536;
        append(stream, loadval(r3, big));
        append(stream, loadval(r4, multiplier));
        append(stream, mul(r4, r3, r4));
        append(stream, add(r4, r3, r4));
        append(stream, nand(r5, r4, r4));
        append(stream, output(r5));
        append(stream, add(r1, r2, r4));
        append(stream, output(r1));
        append(stream, halt());
}

void build_mult_test(Seq_T stream)
{
        append(stream, loadval(r2, 13));
        append(stream, loadval(r3, 5));
        append(stream, mul(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_mult_zero_test(Seq_T stream)
{
        append(stream, loadval(r2, 0));
        append(stream, loadval(r3, 0));
        append(stream, mul(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_mult_one_zero_test(Seq_T stream)
{
        append(stream, loadval(r2, 1));
        append(stream, loadval(r3, 0));
        append(stream, mul(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_mult_div_complex_test(Seq_T stream)
{
        append(stream, loadval(r3, 3));
        append(stream, loadval(r4, 4));
        append(stream, mul(r2, r3, r4));
        append(stream, mul(r1, r4, r3));
        append(stream, divide(r5, r1, r2));
        append(stream, output(r5));
        append(stream, halt());
}

void build_mult_max_test(Seq_T stream)
{
        append(stream, loadval(r3, 65536));
        append(stream, mul(r4, r3, r3));
        append(stream, output(r4));
        append(stream, halt());
}

void build_divide_test(Seq_T stream)
{
        append(stream, loadval(r2, 132));
        append(stream, loadval(r3, 2));
        append(stream, divide(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

// void build_div_zeros_test(Seq_T stream)   // BAD
// {
//         append(stream, loadval(r0, 0));
//         append(stream, divide(r1, r0, r0));
//         append(stream, output(r1));
//         append(stream, halt());
// }

void build_div_0_1_test(Seq_T stream)
{
        append(stream, loadval(r0, 0));
        append(stream, loadval(r1, 1));
        append(stream, divide(r2, r0, r1));
        append(stream, output(r2));
        append(stream, halt());
}

// void build_div_1_0_test(Seq_T stream) // BAD
// {
//         append(stream, loadval(r0, 0));
//         append(stream, loadval(r1, 1));
//         append(stream, divide(r2, r1, r0));
//         append(stream, output(r2));
//         append(stream, halt());
// }

void build_div_7_3_test(Seq_T stream)
{
        append(stream, loadval(r0, 7));
        append(stream, loadval(r1, 3));
        append(stream, divide(r2, r0, r1));
        append(stream, output(r2));
        append(stream, halt());
}

void build_div_3_7_test(Seq_T stream)
{
        append(stream, loadval(r0, 7));
        append(stream, loadval(r1, 3));
        append(stream, divide(r2, r1, r0));
        append(stream, output(r2));
        append(stream, halt());
}

void build_nand_test(Seq_T stream)
{
        append(stream, loadval(r2, 0));
        append(stream, nand(r1, r2, r2));
        append(stream, loadval(r7, 55));
        append(stream, add(r0, r1, r7));
        append(stream, output(r0));
        append(stream, halt());
}

// void build_nand_zeros_test(Seq_T stream) // BAD
// {
//         append(stream, loadval(r2, 0));
//         append(stream, nand(r1, r2, r2));
//         append(stream, output(r1));
//         append(stream, halt());
// }

void build_nand_big_test(Seq_T stream)
{
        uint32_t big = ~0;
        big >>= 16;
        uint32_t multiplier = 65536;
        append(stream, loadval(r3, big));
        append(stream, loadval(r4, multiplier));
        append(stream, mul(r4, r3, r4));  
        append(stream, add(r4, r3, r4));
        append(stream, nand(r1, r4, r4));
        append(stream, output(r1));
        append(stream, halt());
}

void build_input_test(Seq_T stream)
{
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, halt());
}

void build_input_weird_test(Seq_T stream)
{
        append(stream, input(r1));
        append(stream, input(r2));
        append(stream, output(r1));
        append(stream, output(r2));
        append(stream, halt());
}

void build_cond_move_2_test(Seq_T stream)
{
        append(stream, loadval(r2, 0));
        append(stream, loadval(r3, 2));
        append(stream, loadval(r4, 1));
        append(stream, cond_move(r2, r3, r4));
        append(stream, output(r2));
        append(stream, halt());
}

void build_cond_move_0_test(Seq_T stream)
{
        append(stream, loadval(r2, 0));
        append(stream, loadval(r3, 2));
        append(stream, loadval(r4, 0));
        append(stream, cond_move(r2, r3, r4));
        append(stream, output(r2));
        append(stream, halt());
}

void build_cond_move_16_test(Seq_T stream)
{
        append(stream, loadval(r2, 512));
        append(stream, loadval(r3, 16));
        append(stream, loadval(r4, 1024));
        append(stream, cond_move(r2, r3, r4));
        append(stream, output(r2));
        append(stream, halt());
}

void build_map_test(Seq_T stream)
{
        append(stream, loadval(r0, 5));
        append(stream, map(r1, r0));
        append(stream, map(r2, r0));
        append(stream, map(r3, r0));
        append(stream, map(r4, r0));
        append(stream, map(r5, r0));
        append(stream, map(r6, r0));
        append(stream, output(r6));
        append(stream, halt());
}

void build_unmap_test(Seq_T stream)
{
        append(stream, loadval(r0, 5));
        append(stream, map(r1, r0));
        append(stream, unmap(r1));
        append(stream, output(r1));
        append(stream, halt());
}

void build_map_unmap_test(Seq_T stream)
{
        append(stream, loadval(r0, 5));
        append(stream, map(r1, r0));
        append(stream, map(r2, r0));
        append(stream, map(r3, r0));
        append(stream, map(r4, r0));
        append(stream, unmap(r1));
        append(stream, unmap(r4));
        append(stream, map(r5, r0));
        append(stream, map(r6, r0));
        append(stream, map(r7, r0));
        append(stream, output(r1));
        append(stream, output(r2));
        append(stream, output(r3));
        append(stream, output(r4));
        append(stream, output(r5));
        append(stream, output(r6));
        append(stream, output(r7));
        append(stream, halt());
}

// void build_unmap_m0_test(Seq_T stream) // BAD
// {
//         append(stream, loadval(r0, 0));
//         append(stream, unmap(r0));
//         append(stream, halt());
// }

void build_store_load_test(Seq_T stream)
{
        append(stream, loadval(r0, 5));
        append(stream, loadval(r7, 20));
        append(stream, loadval(r6, 3));
        append(stream, map(r1, r0));
        append(stream, seg_store(r1, r6, r7));
        append(stream, seg_load(r4, r1, r6));
        append(stream, output(r4));
        append(stream, halt());
}

void build_load_program_test(Seq_T stream)
{
        append(stream, loadval(r0, 0));
        append(stream, loadval(r1, 7));
        append(stream, output(r1));
        append(stream, load_program(r0, r1));
        append(stream, loadval(r1, 10));
        append(stream, output(r1));
        append(stream, load_program(r0, r1));
        append(stream, loadval(r1, 13));
        append(stream, output(r1));
        append(stream, load_program(r0, r1));
        append(stream, loadval(r1, 16));
        append(stream, output(r1));
        append(stream, load_program(r0, r1));
        append(stream, loadval(r1, 16));
        append(stream, output(r1));
        append(stream, load_program(r0, r1));
        append(stream, halt());
}

void build_load_halt_program_test(Seq_T stream)
{
        append(stream, loadval(r0, 28672));
        append(stream, loadval(r1, 65536));
        append(stream, mul(r2, r0, r1));
        append(stream, loadval(r6, 1));
        append(stream, loadval(r5, 0));
        append(stream, map(r7, r6));
        append(stream, seg_store(r7, r5, r2));
        append(stream, load_program(r7, r5));
        append(stream, output(r6));
        append(stream, halt());
}