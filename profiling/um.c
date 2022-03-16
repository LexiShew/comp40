/*****************************************************************************
 *
 *                                  um.c
 *
 * Assignment: Homework 7 -- profiling
 * Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
 * Date: December 7, 2021
 *
 * This file is the driver file for our UM program. Clients can interact with
 * um.c to run um binaries.
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <sys/stat.h>
#include <stdint.h>


const int BYTES_PER_WORD = 4;
const int WORD_SIZE = 32;

typedef uint32_t Um_instruction;


typedef struct Node {
    struct Node *next;
    int value;
} *Node;


typedef enum Um_opcode {
        COND_MOV = 0, SEG_LOAD, SEG_STORE, ADD, MULT, DIV,
        NAND, HALT, MAP, UNMAP, OUTPUT, INPUT, LOAD_PROGRAM, LOAD_VAL
} Um_opcode;


static inline uint32_t pack_word(unsigned char chars[4]) {
    uint32_t word = 0;
    for (int i = 0; i < 4; i++) {
        word <<= 8;
        word |= chars[i];
    }
    return word;
}


static inline uint32_t getu(uint32_t word, unsigned width, unsigned lsb)
{
        // assert(width <= 32); // invalid
        unsigned hi = lsb + width;
        // assert(hi <= 32);    // invalid
        return word << (32 - hi) >> (32 - width);
}


int main(int argc, char *argv[])
{
    /* make sure that command-line instruction is correct */
    if (argc != 2) {
        fprintf(stderr, "Usage: ./um [UM binary filename]\n");
        exit(EXIT_FAILURE);
    }

    /* get number of instructions */
    struct stat stat_ptr;
    if (stat(argv[1], &stat_ptr) == -1) {
        fprintf(stderr, "Error: Unable to open file\n");
        exit(EXIT_FAILURE);
    }
    int num_instructions = stat_ptr.st_size / BYTES_PER_WORD;

    /* open file */
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    /* make m0 */
    uint32_t *m0 = malloc((num_instructions + 1) * 4);
    assert(m0 != NULL);
    m0[0] = num_instructions;

    /* get instructrustions and pack into 32bit words */
    int curr_char = fgetc(fp);
    unsigned char chars[4];
    for (int i = 0; i < num_instructions; i++) {
        for (int j = 0; j < 4; j++) {
            if (feof(fp)) {
                fprintf(stderr, "Error: file bad\n");
                exit(EXIT_FAILURE);
            }
            chars[j] = curr_char;
            curr_char = fgetc(fp);
        }
        m0[i + 1] = pack_word(chars);
    }
    fclose(fp);

    
    uint32_t r[8] = { 0 };      /* registers */

    /* memory */
    int start_length = 64;
    uint32_t **mem = malloc(start_length * 8);
    assert(mem != NULL);
    mem[0] = m0;
    int total_size = start_length;
    int next_elem = 1;
    
    int program_counter = 0;
    Node rec_list = NULL;

    int keep_running = 1;
    Um_opcode op = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    uint32_t rb;
    uint32_t rc;
    int val = 0;

    while (keep_running == 1) {
        uint32_t word = mem[0][program_counter + 1];
        op = getu(word, 4, WORD_SIZE - 4);

        /* potentially optimize by only getting that values that are needed */
        if (op != LOAD_VAL) {
            c = getu(word, 3, 0);
            b = getu(word, 3, 3);
            a = getu(word, 3, 6);
        } else {
            a = getu(word, 3, WORD_SIZE - 7);
            val = getu(word, 25, 0);
        }

        program_counter++;
        switch (op) {
            case COND_MOV:
                if (r[c] != 0) {
                    r[a] = r[b];
                }
                break;

            case SEG_LOAD:
                r[a] = mem[r[b]][r[c] + 1];
                break;

            case SEG_STORE:
                mem[r[a]][r[b] + 1] = r[c];
                break;

            case ADD:
                r[a] = r[b] + r[c];
                break;

            case MULT:
                r[a] = r[b] * r[c];
                break;

            case DIV:
                r[a] = r[b] / r[c];
                break;

            case NAND:
                r[a] = ~(r[b] & r[c]);
                break;

            case HALT:
                keep_running = 0;
                break;

            case MAP: ;
                rc = r[c];
                int index;
                if (next_elem == total_size) {
                    /* check expansion */
                    mem = realloc(mem, total_size * 8 * 2);
                    total_size *= 2;
                }
                if (rec_list == NULL) {
                    index = next_elem;
                    next_elem++;
                } else {
                    index = rec_list->value;
                    Node temp = rec_list; 
                    rec_list = rec_list->next;
                    free(temp);
                }
                r[b] = index;
                mem[index] = calloc(rc + 1, 4);
                mem[index][0] = rc;
                break;

            case UNMAP: ;
                rc = r[c];
                // assert(rc != 0);     // FAULURE MODE
                /* check that everything you're freeing has been mapped */
                if ((int) rc < next_elem && mem[rc] != NULL) {
                    free(mem[rc]);
                    mem[rc] = NULL;
                }
                Node new_node = malloc(16);
                assert(new_node != NULL);
                new_node->next = rec_list;
                new_node->value = rc;
                rec_list = new_node;
                break;

            case OUTPUT: ;
                rc = r[c];
                // assert(rc <= 255);   // FAILURE MODE
                printf("%c", rc);
                break;

            case INPUT: ;
                int in = getchar();
                if (in == EOF) {
                    r[c] = ~0;
                } else {
                    r[c] = in;
                }
                break;

            case LOAD_PROGRAM: ;
                rb = r[b];
                if (rb != 0) {
                    /* check that everything you're freeing has been mapped */
                    if (mem[0] != NULL) {
                        free(mem[0]);
                    }
                    uint32_t *segment = mem[r[b]];
                    // assert(segment != NULL);     // FAILURE MODE
                    int length = segment[0];
                    mem[0] = malloc((length + 1) * 4);
                    assert(mem[0] != NULL);
                    for (int i = 0; i < length + 1; i++) {
                        mem[0][i] = segment[i];
                    }
                }
                program_counter = r[c];
                break;

            case LOAD_VAL: ;
                r[a] = val;
                break;

            default:
                fprintf(stderr, "Invalid instruction\n");
                exit(EXIT_FAILURE);
        }
    }

    /* free memory */
    for (int i = 0; i < next_elem; i++) {
        if (mem[i] != NULL) {
            free(mem[i]);
        }
    }
    free(mem);
    while (rec_list != NULL) {
        Node temp = rec_list->next;
        free(rec_list);
        rec_list = temp;
    }

    return 0;
}