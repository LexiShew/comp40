#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

void print_mems(Memory_T mem0, Memory_T mem1, Memory_T mem2, Memory_T mem3)
{
    fprintf(stderr, "mem0 (length = %d):\n", Memory_length(mem0));
    Memory_print(mem0);
    fprintf(stderr, "mem1 (length = %d):\n", Memory_length(mem1));
    Memory_print(mem1);
    fprintf(stderr, "mem2 (length = %d):\n", Memory_length(mem2));
    Memory_print(mem2);
    fprintf(stderr, "mem3 (length = %d):\n", Memory_length(mem3));
    Memory_print(mem3);
}


int main()
{
    Memory_T mem0 = Memory_new(10);
    Memory_T mem1 = Memory_new(10);
    Memory_T mem2 = Memory_new(10);
    Memory_T mem3 = Memory_new(10);

    fprintf(stderr, "\n\n---- MEMORY ARCHITECTURE TESTS ----\n");
    fprintf(stderr, "\nPRINT\n");
    print_mems(mem0, mem1, mem2, mem3);

    fprintf(stderr, "\nNEW SEG\n");
    int seg_index = Memory_map_new_segment(mem1, 0, 0);
    fprintf(stderr, "mapping to index %d\n", seg_index);

    seg_index = Memory_map_new_segment(mem2, 3, 7);
    fprintf(stderr, "mapping to index %d\n", seg_index);
    seg_index = Memory_map_new_segment(mem2, 1, 2);
    fprintf(stderr, "mapping to index %d\n", seg_index);
    seg_index = Memory_map_new_segment(mem2, 0, 3);
    fprintf(stderr, "mapping to index %d\n", seg_index);

    seg_index = Memory_map_new_segment(mem3, 2, 1);
    fprintf(stderr, "mapping to index %d\n\n", seg_index);
    print_mems(mem0, mem1, mem2, mem3);

    fprintf(stderr, "\nREG SEG\n");
    uint32_t *new_seg = malloc(4 * sizeof(uint32_t));
    new_seg[0] = 3;
    new_seg[1] = 1;
    new_seg[2] = 2;
    new_seg[3] = 3;
    // seg_index = Memory_map_segment(mem2, 1, new_seg); // error mem2 at m[2] is already mapped
    seg_index = Memory_map_segment(mem3, 1, new_seg);
    fprintf(stderr, "mapping to index %d\n", seg_index);
    print_mems(mem0, mem1, mem2, mem3);


    fprintf(stderr, "\nSET WORD\n");
    Memory_set_word(mem3, 2, 0, 3);
    print_mems(mem0, mem1, mem2, mem3);
    Memory_set_word(mem3, 2, 0, 4);
    print_mems(mem0, mem1, mem2, mem3);

    // Memory_set_word(mem3, 2, 1, 4);  // error: out of bounds

    // Memory_set_word(mem2, 2, 1, 4);  // error: mem2's m[2] is NULL

    Memory_set_word(mem2, 3, 0, 3);
    Memory_set_word(mem2, 3, 1, 4);
    Memory_set_word(mem2, 3, 2, 5);
    Memory_set_word(mem2, 3, 3, 6);
    Memory_set_word(mem2, 3, 4, 7);
    Memory_set_word(mem2, 3, 5, 8);
    Memory_set_word(mem2, 3, 6, 9);
    // Memory_set_word(mem2, 0, 7, 10);  // seg fault -- accessing index out of range
    print_mems(mem0, mem1, mem2, mem3);

    fprintf(stderr, "\nGET WORD\n");
    // int val = Memory_get_word(mem2, 2, 1);  // error: mem2's m[2] is null
    int val = Memory_get_word(mem2, 3, 0);
    fprintf(stderr, "    val = %x\n", val);
    val = Memory_get_word(mem2, 3, 1);
    fprintf(stderr, "    val = %x\n", val);
    val = Memory_get_word(mem2, 3, 2);
    fprintf(stderr, "    val = %x\n", val);
    val = Memory_get_word(mem2, 3, 3);
    fprintf(stderr, "    val = %x\n", val);
    val = Memory_get_word(mem2, 3, 4);
    fprintf(stderr, "    val = %x\n", val);
    val = Memory_get_word(mem2, 3, 5);
    fprintf(stderr, "    val = %x\n", val);
    val = Memory_get_word(mem2, 3, 6);
    fprintf(stderr, "    val = %x\n", val);

    // val = Memory_get_word(mem2, 3, 7);      // seg fault -- accessing index out of range
    print_mems(mem0, mem1, mem2, mem3);

    fprintf(stderr, "\nUNMAP\n");
    Memory_unmap_segment(mem2, 0);
    Memory_unmap_segment(mem3, 0);
    print_mems(mem0, mem1, mem2, mem3);


    fprintf(stderr, "\nFREE\n");
    Memory_free(&mem0);
    Memory_free(&mem1);
    Memory_free(&mem2);
    Memory_free(&mem3);
    /* seg fault because all data are freed
        print_mems(mem0, mem1, mem2, mem3);
    */

    fprintf(stderr, "\n-----------------------------------\n\n\n");
}