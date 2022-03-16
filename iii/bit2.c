/**************************************************************
 *
 *                     bit2.c
 *
 * Assignment: Homework 2 -- iii
 * Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 * Date: October 4, 2021
 *     
 * This file contains the implementation of the Bit2 data structure.
 * This data structure is a 2-D (a.k.a matrix) of bits, and has a
 * variety of getter, setter, and memory functions that can alter
 * and give information about the contents of the matrix.
 *
 **************************************************************/

#include "bit2.h"
#include <uarray.h>
#include <assert.h>
#include <stdio.h>
#include <mem.h>
#include <bit.h>

/* Bit2_T (struct)
 * Description: This is the Bit2_T struct that gets
 * passed into most of our functions. It contains
 * an integer storing the height of the matrix,
 * an integer storing the width fo the matrix and a
 * a parent array of the UArray_T type that contains
 * our data as bytes.
 *
*/
struct Bit2_T {
    int width;
    int height;

    UArray_T parentArray;
};

/* 
 * Bit2_new
 * Input: width and the height of the new bit array
 * Output: a new Bit2 struct matrix
 * Description: allocates memory for a new Bit2_T matrix which is  
 * implemented using a UArray_T parent array storing elements of
 * type Bit_T. The new matrix is unintialized. 
*/
Bit2_T Bit2_new(int width, int height)
{
    assert(width >= 0);
    assert(height >= 0);

    Bit2_T array;
    NEW(array);

    array->width = width;
    array->height = height;
   
    UArray_T parentArray = UArray_new(width + 1, sizeof(Bit_T*));
    
    for (int i = 0; i < width + 1; i++) {
        *(Bit_T*) UArray_at(parentArray, i) = Bit_new(height + 1);
    }

    array->parentArray = parentArray;
    return array;
}


/* 
 * Bit2_width
 * Input: a Bit2 struct matrix
 * Output: the width of the matrix
 * Description: asserts that the matrix is not null, 
 * then returns the width element of the struct.
 * 
*/
int Bit2_width(Bit2_T bit2)
{
    assert(bit2 != NULL);
    return bit2->width;
}


/* 
 * Bit2_height
 * Input: a Bit2 struct matrix
 * Output: the width of the matrix
 * Description: asserts that the matrix is not null, 
 * then returns the height element of the struct.
 * 
*/
int Bit2_height(Bit2_T bit2)
{
    assert(bit2 != NULL);
    return bit2->height;
}



/*  
 * Bit2_get
 * Input: a Bit2 matrix and the column and row the user is looking for
 * Output: the bit at that column-row position as an integer (1 or 0)
 * Description: asserts that the matrix passed in is not null and
 * the specified column and width are within the bounds of the matrix,
 * throws a checked runtime error otherwise.
 * Returns the bit at the column and row as an integer. 
*/
int Bit2_get(Bit2_T bit2, int col, int row)
{
    assert(bit2 != NULL);
    assert(col >= 0 && col < Bit2_width(bit2));
    assert(row >= 0 && row < Bit2_height(bit2));

    int bit;
    bit = Bit_get(*(Bit_T*) UArray_at(bit2->parentArray, col), row);
    return bit;
}


/* 
 * Bit2_put
 * Input: a Bit2 matrix, integers representing column and row, and
 *        an integer bit to change the value at that position to.
 * Output: an integer representing the previous bit at that position.
 * Description: asserts that the matrix passed in is not null and
 * the specified column and width are within the bounds of the matrix, 
 * and that the integer passed in is either 1 or 0, throws a checked 
 * runtime error otherwise.
 * Returns the former bit by casting the output of Hanson's Bit and
 * UArray's functions. 
 * 
*/
int Bit2_put(Bit2_T bit2, int col, int row, int bit)
{
    assert(bit2 != NULL);
    assert(col >= 0 && col < Bit2_width(bit2));
    assert(row >= 0 && row < Bit2_height(bit2));
    assert(bit == 0 || bit == 1);
    return (int) Bit_put(*(Bit_T*) UArray_at(bit2->parentArray, col), row, bit);
}



/* 
 * Bit2_map_col_major
 * Input: a Bit2 matrix, a function to apply onto the matrix, and a void 
 *        pointer to use as a closure
 * Output: none
 * Description: iterates through the Bit2 matrix and applies a function
 * to all of the elements column by column. Uses functions of Bit2
 * including Bit2_height, Bit2_width, and Bit2_get.
*/
void Bit2_map_col_major(Bit2_T bit2, void f(int col, int row, Bit2_T bit2, 
                                        int currValue, void *p2), void *cl)
{
    assert(bit2 != NULL);
    assert(cl != NULL);
    
    int height = Bit2_height(bit2);
    int width = Bit2_width(bit2);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int bit = Bit2_get(bit2, i, j);
            f(i, j, bit2, bit, cl);
        }
    } 
}

/* 
 * Bit2_map_col_major
 * Input: a Bit2 matrix, a function to apply onto the matrix, and a void 
 *        pointer to use as a closure
 * Output: none
 * Description: iterates through the Bit2 matrix and applies a function
 * to all of the elements row by row. Uses functions of Bit2
 * including Bit2_height, Bit2_width, and Bit2_get.
*/
void Bit2_map_row_major(Bit2_T bit2, void f(int col, int row, Bit2_T bit2, 
                                             int int1, void *p2), void *cl)
{
    assert(bit2 != NULL);
    assert(cl != NULL);

    int height = Bit2_height(bit2);
    int width = Bit2_width(bit2);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            int bit = Bit2_get(bit2, j, i);
            f(j, i, bit2, bit, cl);
        }
    }
}


/*
 * Bit2_free
 * Input: a pointer to a Bit2 matrix
 * Output: none
 * Description: asserts that the pointer of bit2 object 
 * and bit2 object itself is not null, then iterates
 * through the parent array of bit2 and frees each element,
 * and then finally frees the pointer
 * 
*/
void Bit2_free(Bit2_T *bit2)
{
    assert(bit2 != NULL && *bit2 != NULL);
    for (int i = 0; i < (*bit2)->width + 1; i++) {
        Bit_free(UArray_at((*bit2)->parentArray, i));
    }
    UArray_free(&(*bit2)->parentArray);
    FREE(*bit2);

}