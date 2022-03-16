/*****************************************************************************
 *
 *                                  um.c
 *
 * Assignment: Homework 6 -- UM
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: November 23, 2021
 *
 * This file is the driver file for our UM program. Clients can interact with
 * um.c to run um binaries.
 *
 ****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mem.h>
#include <sys/stat.h>
#include "init.h"
#include "um_run.h"

const int BYTES_PER_WORD = 4;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./um [UM binary filename]\n");
        exit(EXIT_FAILURE);
    }

    struct stat stat_ptr;
    if (stat(argv[1], &stat_ptr) == -1) {
        fprintf(stderr, "Error: Unable to open file\n");
        exit(EXIT_FAILURE);
    }
    int num_instructions = stat_ptr.st_size / BYTES_PER_WORD;

    uint32_t *m0 = ALLOC((num_instructions + 1) * sizeof(uint32_t));
    m0[0] = num_instructions;
    get_m0(argv[1], m0, num_instructions);

    um_run(m0);

    return 0;
}