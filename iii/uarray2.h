/**************************************************************
 *
 *                     uarray2.h
 *
 * Assignment: Homework 2 -- iii
 * Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 * Date: October 4, 2021
 *     
 * This file contains the interface of the UArray2 data structure.
 * This data structure is a 2-D (a.k.a matrix) of unboxed types,
 * and has a variety of getter, setter, and memory functions that
 * can alter and give information about the contents of the matrix.
 *
 **************************************************************/

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray2_T
typedef struct T *T;


/* 
 * UArray2_new
 * Input: the width height and element size of the new UArray2
 * Output: a pointer to a new UArray object
 * Description: creates a new UArray2 matrix of width columns and height rows
 * and returns a UArray2 matrix 
 * Logical Expectation: width and height must be greater than 0
*/
extern T UArray2_new(int width, int height, int elemSize);


/* 
 * UArray2_width
 * Input: a pointer to an UArray2 object
 * Output: the UArray2 matrix's width
 * Description: returns the width (number of columns) of the UArray2 matrix
 * Logical Expectation: UArray2 cannot be null
*/
extern int UArray2_width(T uarray2);


/* 
 * UArray2_height
 * Input: a pointer to an UArray2 object
 * Output: the UArray2 matrix's height
 * Description: returns the height (number of rows) of the UArray2 matrix
 * Logical Expectation: UArray2 cannot be null
 * 
*/
extern int UArray2_height(T uarray2);


/* 
 * UArray2_size
 * Input: a pointer to an UArray2 object
 * Output: the UArray2 matrix's element size
 * Description:takes in a UArray2 and returns the element size
            of the matrix
 * Logical Expectation: UArray2 is not null
 * 
*/
extern int UArray2_size(T uarray2);


/*  
 * UArray2_at
 * Input: a pointer to an UArray2 object and the column and row
 *      the user is looking for
 * Output: a pointer to the value at the specified column and row
 *  Description: returns the value stored in the matrix passed in
 *               at the specified column and row
 *  Logical Expectations: UArray2 cannot be null, col and row must
 *              be within width and height of matrix
*/
extern void* UArray2_at(T uarray2, int col, int row);


/* 
 * UArray2_map_col_major
 * Input: a pointer to an UArray2 matrix, a function to be applied onto
 *      each element of the matrix, and a closure pointer
 * Output: none
 * Description: applies a function f to every element in the matrix UArray2 in
 *              column-major fashion, starting from (col, row) = (0,0) and
 *              applying f to each element in a column before applying to
 *              the next column
 * Logical Expectation: UArray2 is not null 
 * 
*/
extern void UArray2_map_col_major(T uarray2, void f(int, int, T, void*, void*),
                                                                        void*);


/* 
 * UArray2_map_row_major
 * Input: a pointer to an UArray2 matrix, a function to be applied onto
 *      each element of the matrix, and a closure pointer
 * Output: none
 * Description: applies a function f to every element in the matrix UArray2 in
 *              row-major fashion, starting from (col, row) = (0,0) and
 *              applying f to each element in a row before applying to the
 *              next row
 * Logical Expectation: UArray2 is not null
*/
extern void UArray2_map_row_major(T uarray2, void f(int, int, T, void*, void*),
                                                                        void*);


/*
 * UArray2_free
 * Input: a pointer to a UArray2 object
 * Output: none
 * Description: deallocates memory associated with UArray2 vector
 * Logical Expectation: UArray2 is not null
 * 
*/
extern void UArray2_free(T *uarray2);

#undef T
# endif