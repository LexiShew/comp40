/**************************************************************
 *
 *                     ypp-compressed.c
 *
 * Assignment: Homework 4 -- arith
 * Authors: Lexi Shewchuk (ashewc01), Deanna Oei (doei01)
 * Date: October 27, 2021
 *     
 * Converts ypps to ypp_structs and back.
 * Contains implementations for functions:
    convert_ypp_to_compressed
    convert_compressed_to_ypp
    ypp_to_compressed_A2
    compressed_to_ypp_A2
    ypp_to_compressed_apply
    compressed_to_ypp_apply
 *
 **************************************************************/

#include "ypp-compressed.h"
#include "a2methods.h"
#include "a2plain.h"
#include <assert.h>
#include <stdio.h>
#include <mem.h>
#include "arith40.h"

typedef A2Methods_UArray2 A2;

typedef struct Ypp_struct
{
    float y;
    float pb;
    float pr;
} *Ypp_struct;

typedef struct Compressed_struct {
     float a;
     float b;
     float c;
     float d;
     unsigned pb_index;
     unsigned pr_index;
} *Compressed_struct;
 
typedef struct Ypp_block_struct {
    Ypp_struct ypp1;
    Ypp_struct ypp2;
    Ypp_struct ypp3;
    Ypp_struct ypp4;
} *Ypp_block_struct;


void ypp_to_compressed_apply(int i, int j, A2 ypp_A2, void *elem, 
                            void *compressed_A2);
void compressed_to_ypp_apply(int i, int j, A2 compressed_A2, void *elem, 
                            void *ypp_A2);

/*
 * clamp
 * Behavior: Helper function. Checks if given value is between -0.3 and 0.3.
    If it's below, round to -0.3. If it's above, round to 0.3.
 * Parameters: float curr_val (which will be checked)
 * Returns: float curr_val (now guaranteed to be) between -0.3 and 0.3
 * Expectations/errors: none
 */
float clamp(float curr_val)
{
    if (curr_val < -0.3) {
        return -0.3;
    }
    
    if (curr_val > 0.3) {
        return 0.3;
    }

    return curr_val;
}

/* conversion functions */
/*
 * convert_RGB_to_YPP
 * Behavior: compresses a ypp (component video representation) by taking
        average values and inserting them into a compressed_struct
 * Parameters: Ypp_block_struct block which contains 4 ypps
 * Returns: compressed_struct containing the average values from a 
        compressed ypp
 * Expectations/errors: 
    block is not null
 */
Compressed_struct convert_ypp_to_compressed(Ypp_block_struct block)
{
    assert(block != NULL);

    Compressed_struct comp;
    NEW(comp);

    comp->a = (block->ypp4->y + block->ypp3->y + 
                block->ypp2->y + block->ypp1->y) / 4.0;
    comp->b = clamp((block->ypp4->y + block->ypp3->y - 
                block->ypp2->y - block->ypp1->y) / 4.0);
    comp->c = clamp((block->ypp4->y - block->ypp3->y + 
                block->ypp2->y - block->ypp1->y) / 4.0);
    comp->d = clamp((block->ypp4->y - block->ypp3->y - 
                block->ypp2->y + block->ypp1->y) / 4.0);

    comp->pb_index = Arith40_index_of_chroma(
                    (block->ypp4->pb + block->ypp3->pb + 
                        block->ypp2->pb + block->ypp1->pb) / 4.0);
    comp->pr_index = Arith40_index_of_chroma(
                    (block->ypp4->pr + block->ypp3->pr + 
                        block->ypp2->pr + block->ypp1->pr) / 4.0);

    return comp;
}

/*
 * convert_compressed_to_ypp
 * Behavior: converts a compressed ypp to a ypp_block_struct which 
    contains values for 4 ypps
 * Parameters: compressed_struct
 * Returns: ypp_block_struct
 * Expectations/errors: comp should not be null
 */
Ypp_block_struct convert_compressed_to_ypp(Compressed_struct comp)
{
    assert(comp != NULL);
    Ypp_struct ypp1;
    Ypp_struct ypp2;
    Ypp_struct ypp3;
    Ypp_struct ypp4;
    NEW(ypp1);
    NEW(ypp2);
    NEW(ypp3);
    NEW(ypp4);

    float a = comp->a;
    float b = comp->b;
    float c = comp->c;
    float d = comp->d;
    float pb = Arith40_chroma_of_index(comp->pb_index);
    float pr = Arith40_chroma_of_index(comp->pr_index);

    ypp1->y = a - b - c + d;
    ypp2->y = a - b + c - d;
    ypp3->y = a + b - c - d;
    ypp4->y = a + b + c + d;

    ypp1->pb = pb;
    ypp2->pb = pb;
    ypp3->pb = pb;
    ypp4->pb = pb;

    ypp1->pr = pr;
    ypp2->pr = pr;
    ypp3->pr = pr;
    ypp4->pr = pr;
    
    Ypp_block_struct block;
    NEW(block);

    block->ypp1 = ypp1;
    block->ypp2 = ypp2;
    block->ypp3 = ypp3;
    block->ypp4 = ypp4;

    return block;
}

 /*
 * ypp_to_compressed_A2
 * Behavior: convert A2 of ypps to a compressed A2 using an apply function
 *      ypp_to_compressed_apply with row major mapping
 * Parameters: A2 of ypps
 * Returns: A2 of compressed values
 * Expectations/errors: 
 */
A2 ypp_to_compressed_A2(A2 ypp_A2)
{
    int width = uarray2_methods_plain->width(ypp_A2) / 2;
    int height = uarray2_methods_plain->height(ypp_A2) / 2;

    A2 compressed_A2 = uarray2_methods_plain->new(width, height, 
                            sizeof(struct Compressed_struct));

    uarray2_methods_plain->map_default(ypp_A2, ypp_to_compressed_apply, 
                                            compressed_A2);

    return compressed_A2;
}

/*
 * compressed_to_ypp_A2
 * Behavior: convert compressed A2 to an A2 of ypp values using apply
 *     function compressed_to_ypp_apply with row major mapping
 * Parameters: A2 compressed_A2, A2Methods_T meth
 * Returns: A2 of ypp values
 * Expectations/errors: compressed_A2 is not null
 */
A2 compressed_to_ypp_A2(A2 compressed_A2) {
    assert(compressed_A2 != NULL);
    int width = uarray2_methods_plain->width(compressed_A2) * 2;
    int height = uarray2_methods_plain->height(compressed_A2) * 2;

    A2 ypp_A2 = uarray2_methods_plain->new(width, height, 
                                            sizeof(struct Ypp_struct)); 

    uarray2_methods_plain->map_default(compressed_A2, 
                                compressed_to_ypp_apply, ypp_A2);

    return ypp_A2;
}

/*
 * compressed_to_ypp_apply
 * Behavior: converts ypp_A2 into a compressed A2
 * Parameters: 
    int i
    int j
    A2 ypp_A2
    void *elem
    void *compressed_A2
 * Returns: none
 * Expectations/errors: compressed_A2 not null
 */
void ypp_to_compressed_apply(int i, int j, A2 ypp_A2, void *elem, 
                                void *compressed_A2)
{
    (void) ypp_A2;
    (void) elem;
    assert(compressed_A2 != NULL);

    if (i % 2 == 0 && j % 2 == 0) {
        Ypp_block_struct block;
        NEW(block);
        block->ypp1 = uarray2_methods_plain->at(ypp_A2, i, j);
        block->ypp2 = uarray2_methods_plain->at(ypp_A2, i + 1, j);
        block->ypp3 = uarray2_methods_plain->at(ypp_A2, i, j + 1);
        block->ypp4 = uarray2_methods_plain->at(ypp_A2, i + 1, j + 1);

        Compressed_struct comp = convert_ypp_to_compressed(block);

        *(Compressed_struct) uarray2_methods_plain->at(compressed_A2, 
                                                        i / 2, j / 2) = *comp;

        FREE(block);
        FREE(comp);
    }
}

/*
 * compressed_to_ypp_apply
 * Behavior: set ypp A2 values to ypp values from block of 4 ypps
 * Parameters: 
    int i
    int j
    A2 compressed_A2
    void *elem
    void *ypp_A2
 * Returns: none
 * Expectations/errors: elem and ypp_A2 are not null
 */
void compressed_to_ypp_apply(int i, int j, A2 compressed_A2, void *elem, 
                                void *ypp_A2)
{
    assert(elem != NULL);
    assert(ypp_A2 != NULL);
    (void) compressed_A2;

    Ypp_block_struct block = convert_compressed_to_ypp(elem);

    *(Ypp_struct) uarray2_methods_plain->at(ypp_A2, (i * 2), (j * 2)) = 
        *(block->ypp1);
    *(Ypp_struct) uarray2_methods_plain->at(ypp_A2, (i * 2) + 1, (j * 2)) =
        *(block->ypp2);
    *(Ypp_struct) uarray2_methods_plain->at(ypp_A2, (i * 2), (j * 2) + 1) =
        *(block->ypp3);
    *(Ypp_struct) uarray2_methods_plain->at(ypp_A2, 
                                            (i * 2) + 1, 
                                            (j * 2) + 1) = *(block->ypp4);

    FREE(block->ypp1);
    FREE(block->ypp2);
    FREE(block->ypp3);
    FREE(block->ypp4);
    FREE(block);
}