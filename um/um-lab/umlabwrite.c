#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assert.h"
#include "fmt.h"
#include "seq.h"

extern void Um_write_sequence(FILE *output, Seq_T instructions);

extern void build_halt_test(Seq_T instructions);
extern void build_verbose_halt_test(Seq_T instructions);
extern void build_print_six_test(Seq_T instructions);

extern void build_add_test(Seq_T instructions);



extern void build_divide_test(Seq_T instructions);

extern void build_map_test(Seq_T instructions);
extern void build_unmap_test(Seq_T instructions);
extern void build_map_unmap_test(Seq_T instructions);
// extern void build_unmap_m0_test(Seq_T stream); // BAD
extern void build_store_load_test(Seq_T instructions);

extern void build_load_extreme_test(Seq_T stream);
// extern void build_load_bad_test(Seq_T stream); // BAD
extern void build_add_zeros_test(Seq_T stream);
extern void build_add_zero_three_test(Seq_T stream);
extern void build_add_three_zero_test(Seq_T stream);
extern void build_add_15_20_test(Seq_T stream);
extern void build_add_big_test(Seq_T stream);

extern void build_mult_test(Seq_T instructions);
extern void build_mult_zero_test(Seq_T instructions);
extern void build_mult_one_zero_test(Seq_T instructions);
extern void build_mult_div_complex_test(Seq_T instructions);
extern void build_mult_max_test(Seq_T instructions);

// extern void build_div_zeros_test(Seq_T stream); // BAD
extern void build_div_0_1_test(Seq_T stream);
// extern void build_div_1_0_test(Seq_T stream); // BAD
extern void build_div_7_3_test(Seq_T stream);
extern void build_div_3_7_test(Seq_T stream);

extern void build_nand_test(Seq_T instructions);
// extern void build_nand_zeros_test(Seq_T instructions); // BAD
extern void build_nand_big_test(Seq_T instructions);

extern void build_input_test(Seq_T instructions);
extern void build_input_weird_test(Seq_T stream);

extern void build_cond_move_2_test(Seq_T stream);
extern void build_cond_move_0_test(Seq_T stream);
extern void build_cond_move_16_test(Seq_T stream);


extern void build_load_program_test(Seq_T stream);
extern void build_load_halt_program_test(Seq_T stream);



/* The array `tests` contains all unit tests for the lab. */

static struct test_info {
        const char *name;
        const char *test_input;          /* NULL means no input needed */
        const char *expected_output;
        /* writes instructions into sequence */
        void (*build_test)(Seq_T stream);
} tests[] = {
        { "halt",         NULL, "", build_halt_test },
        { "halt-verbose", NULL, "", build_verbose_halt_test },
        { "print-six", NULL, "6", build_print_six_test },
        { "load-extreme", NULL, "", build_load_extreme_test },
        // { "load-bad", NULL, "", build_load_bad_test }, // BAD
        { "add", NULL, "3", build_add_test },
        { "add-zeros", NULL, "", build_add_zeros_test },
        { "add-zero-three", NULL, "", build_add_zero_three_test },
        { "add-three-zero", NULL, "", build_add_three_zero_test },
        { "add-15-20", NULL, "", build_add_15_20_test },
        { "add-big", NULL, "", build_add_big_test },


        { "mult", NULL, "A", build_mult_test },
        { "mult-zero", NULL, "", build_mult_zero_test },
        { "mult-one-zero", NULL, "", build_mult_one_zero_test },
        { "mult-div-complex", NULL, "", build_mult_div_complex_test },
        { "mult-max", NULL, "", build_mult_max_test },

        { "divide", NULL, "B", build_divide_test },
        // { "div-zeros", NULL, "", build_div_zeros_test },     // BAD
        { "div-0-1", NULL, "", build_div_0_1_test },
        // { "div-1-0", NULL, "", build_div_1_0_test },         // BAD
        { "div-7-3", NULL, "", build_div_7_3_test },
        { "div-3-7", NULL, "", build_div_3_7_test },

        { "nand", NULL, "", build_nand_test },
        // { "nand-zeros", NULL, "", build_nand_zeros_test },   // BAD
        { "nand-big", NULL, "", build_nand_big_test },

        { "input", NULL, "", build_input_test },
        { "input-weird", NULL, "", build_input_weird_test },

        { "cond-move-2", NULL, "", build_cond_move_2_test },
        { "cond-move-0", NULL, "", build_cond_move_0_test },
        { "cond-move-16", NULL, "", build_cond_move_16_test },

        { "map", NULL, "", build_map_test },
        { "unmap", NULL, "", build_unmap_test },
        { "map-unmap", NULL, "", build_map_unmap_test }, 
        // { "unmap-m0", NULL, "", build_unmap_m0_test },       // BAD
        { "store-load", NULL, "", build_store_load_test },
        { "load-program", NULL, "", build_load_program_test },
        { "load-halt-program", NULL, "", build_load_halt_program_test }
};

  
#define NTESTS (sizeof(tests)/sizeof(tests[0]))

/*
 * open file 'path' for writing, then free the pathname;
 * if anything fails, checked runtime error
 */
static FILE *open_and_free_pathname(char *path);

/*
 * if contents is NULL or empty, remove the given 'path', 
 * otherwise write 'contents' into 'path'.  Either way, free 'path'.
 */
static void write_or_remove_file(char *path, const char *contents);

static void write_test_files(struct test_info *test);


int main (int argc, char *argv[])
{
        bool failed = false;
        if (argc == 1)
                for (unsigned i = 0; i < NTESTS; i++) {
                        printf("***** Writing test '%s'.\n", tests[i].name);
                        write_test_files(&tests[i]);
                }
        else
                for (int j = 1; j < argc; j++) {
                        bool tested = false;
                        for (unsigned i = 0; i < NTESTS; i++)
                                if (!strcmp(tests[i].name, argv[j])) {
                                        tested = true;
                                        write_test_files(&tests[i]);
                                }
                        if (!tested) {
                                failed = true;
                                fprintf(stderr,
                                        "***** No test named %s *****\n",
                                        argv[j]);
                        }
                }
        return failed; /* failed nonzero == exit nonzero == failure */
}


static void write_test_files(struct test_info *test)
{
        FILE *binary = open_and_free_pathname(Fmt_string("%s.um", test->name));
        Seq_T instructions = Seq_new(0);
        test->build_test(instructions);
        Um_write_sequence(binary, instructions);
        Seq_free(&instructions);
        fclose(binary);

        write_or_remove_file(Fmt_string("%s.0", test->name),
                             test->test_input);
        write_or_remove_file(Fmt_string("%s.1", test->name),
                             test->expected_output);
}


static void write_or_remove_file(char *path, const char *contents)
{
        if (contents == NULL || *contents == '\0') {
                remove(path);
        } else {
                FILE *input = fopen(path, "wb");
                assert(input != NULL);

                fputs(contents, input);
                fclose(input);
        }
        free(path);
}


static FILE *open_and_free_pathname(char *path)
{
        FILE *fp = fopen(path, "wb");
        assert(fp != NULL);

        free(path);
        return fp;
}
