/**************************************************************
 *
 *                     uarray2.c
 *
 * Assignment: Homework 2 -- iii
 * Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 * Date: October 4, 2021
 *     
 * This file contains the implementation for the UArray2 data structure.
 * This data structure is a 2-D (a.k.a matrix) of unboxed types,
 * and has a variety of getter, setter, and memory functions that
 * can alter and give information about the contents of the matrix.
 *
 **************************************************************/

#include "uarray2.h"
#include <stdio.h>
#include <uarray.h>
#include <mem.h>
#include <stdbool.h>
#include <assert.h>

struct UArray2_T {
    int width;
    int height;
    int elemSize;
    UArray_T parentArray;
};


/* 
 * UArray2_new
 * Input: the width height and element size of the new UArray2
 * Output: a pointer to a new UArray object
 * Description: asserts that the specified width and height
 * are not negative and that the element size is greater than 0. 
 * Iterates throught the parent array of UArray2 and allocates
 * new memory for each element.
*/
UArray2_T UArray2_new(int width, int height, int elemSize)
{

    assert(width >= 0);
    assert(height >= 0);
    assert(elemSize > 0);

    UArray2_T array;
    NEW(array);

    array->width = width;
    array->height = height;
    array->elemSize = elemSize;
   
    UArray_T parentArray = UArray_new(width + 1, sizeof(UArray_T*));
    
    for (int i = 0; i < width + 1; i++) {
        *(UArray_T*) UArray_at(parentArray, i) = UArray_new(height + 1, elemSize);
    }

    array->parentArray = parentArray;
    return array;
}


/* 
 * UArray2_width
 * Input: a pointer to an UArray2 object
 * Output: the UArray2 matrix's width
 * Description: asserts that the specified pointer is not null
 * and returns the width of the uarray2
*/
int UArray2_width(UArray2_T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->width;
}



/* 
 * UArray2_height
 * Input: a pointer to an UArray2 object
 * Output: the UArray2 matrix's height
 * Description: asserts that the specified pointer is not null
 * and returns the height of the uarray2
 * 
*/
int UArray2_height(UArray2_T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->height;

}


/* 
 * UArray2_size
 * Input: a pointer to an UArray2 object
 * Output: the UArray2 matrix's element size
 * Description:takes in a UArray2 and returns the element size
            of the matrix
 * Description: asserts that the specified pointer is not null
 * and takes the element size of the uarray2
*/
int UArray2_size(UArray2_T uarray2)
{
    assert(uarray2 != NULL);
    return uarray2->elemSize;
}

/*  
 * UArray2_at
 * Input: a pointer to an UArray2 object and the column and row
 *      the user is looking for
 * Output: a pointer to the value at the specified column and row
  * Description: asserts that the matrix passed in is not null and
 * the specified column and width are within the bounds of the matrix, 
 * and that the integer passed in is either 1 or 0, throws a checked 
 * runtime error otherwise.
 * Returns the former bit by casting the output of Hanson's 
 * UArray's functions. 
 */
void* UArray2_at(UArray2_T uarray2, int col, int row)
{
    assert(uarray2 != NULL);
    assert(col >= 0 && col < UArray2_width(uarray2));
    assert(row >= 0 && row < UArray2_height(uarray2));
 
    UArray_T *pointer;
    pointer = UArray_at(*(UArray_T*) UArray_at(uarray2->parentArray, col),
                                                                       row);
    return pointer;
}


/* 
 * UArray2_map_col_major
 * Input: a pointer to an UArray2 matrix, a function to be applied onto
 *      each element of the matrix, and a closure pointer
 * Output: none
  * Description: iterates through the UArray matrix and applies a function
 * to all of the elements column by column. Uses functions of UArray
 * including UArray_height, UArray_width, and UArray_get.
*/
void UArray2_map_col_major(UArray2_T uarray2, void f(int col, int row,
                                UArray2_T uarray2, void*p1, void *p2),
                                                            void *cl)
{

    assert(uarray2 != NULL);
    assert(cl != NULL);

    int height = UArray2_height(uarray2);
    int width = UArray2_width(uarray2);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            void *currentPointer= UArray2_at(uarray2, i, j);
            f(i, j, uarray2, currentPointer, cl);
        }
    }

}



/* 
 * UArray2_map_row_major
 * Input: a pointer to an UArray2 matrix, a function to be applied onto
 *      each element of the matrix, and a closure pointer
 * Output: none
 * Description: iterates through the UArray2 matrix and applies a function
 * to all of the elements row by row. Uses functions of UArray2
 * including UArray2_height, UArray2_width, and UArray2_get.
*/
void UArray2_map_row_major(UArray2_T uarray2, void f(int col, int row,
                                UArray2_T uarray2, void*p1, void *p2),
                                                            void *cl)
{

    assert(uarray2 != NULL);
    assert(cl != NULL);
    
    int height = UArray2_height(uarray2);
    int width = UArray2_width(uarray2);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            void *currentPointer = UArray2_at(uarray2, j, i);
            f(j, i, uarray2, currentPointer, cl);
        }
    }
}



/*
 * UArray2_free
 * Input: a pointer to a UArray2 object
 * Output: none
 * Description: asserts that the pointer of UArray2 object 
 * and UArray2 object itself is not null, then iterates
 * through the parent array of UArray2 and frees each element,
 * and then finally frees the pointer
 * 
*/
void UArray2_free(UArray2_T *uarray2)
{
    assert(uarray2 != NULL && *uarray2 != NULL);

    for (int i = 0; i < (*uarray2)->width + 1; i++) {
        UArray_free(UArray_at((*uarray2)->parentArray, i));
    }
    UArray_free(&(*uarray2)->parentArray);
    FREE(*uarray2);
}