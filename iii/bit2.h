/**************************************************************
 *
 *                     bit2.h
 *
 * Assignment: Homework 2 -- iii
 * Authors: Lexi Shewchuk (ashewc01), Maggie Cheng (ycheng13)
 * Date: October 4, 2021
 *     
 * This file contains the interface of the Bit2 data structure.
 * This data structure is a 2-D (a.k.a matrix) of bits, and has a
 * variety of getter, setter, and memory functions that can alter
 * and give information about the contents of the matrix.
 *
 **************************************************************/

#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#define T Bit2_T
typedef struct T *T;

/* 
 * Bit2_new
 * Input: width and the height of the new bit array
 * Output: a new Bit2 struct matrix
 * Description: creates a new Bit2 matrix of width columns and height rows
 *              and returns a Bit2 matrix 
 * Logical Expectation: width and height must be greater than 0
*/
extern T Bit2_new(int width, int height);


/* 
 * Bit2_width
 * Input: a Bit2 struct matrix
 * Output: the width of the matrix
 * Description: returns the width (number of columns) of the Bit2 matrix
 * Logical Expectation: Bit2 cannot be null
 * 
*/
extern int Bit2_width(T Bit2);


/* 
 * Bit2_height
 * Input: a Bit2 struct matrix
 * Output: the width of the matrix
 * Description: returns the height (number of rows) of the Bit2 matrix
 * Logical Expectation: Bit2 is not null
 * 
*/
extern int Bit2_height(T Bit2);


/*  
 * Bit2_get
 * Input: a Bit2 matrix and the column and row the user is looking for
 * Output: the bit at that column-row position as an integer (1 or 0)
 *  Description: returns the bit stored in the bit matrix passed in
 *               at the specified column and row
 *  Logical Expectations: Bit2 cannot be null, col and row must
 *              be within width and height of matrix
*/
extern int Bit2_get(T Bit2, int col, int row);


/* 
 * Bit2_put
 * Input: a Bit2 matrix, integers representing column and row, and
 *        an integer bit to change the value at that position to.
 * Output: an integer representing the previous bit at that position.
 * Description: takes in a bit matrix and sets the value at the
                specified column and row to the specified bit value.
                returns the previous bit value.
 * Logical Expectation: Bit2 cannot be null, col and row must be within
                width and height of matrix, bit must be 0 or 1. 
                return value will always be 0 or 1.
 * 
*/
extern int Bit2_put(T Bit2, int col, int row, int bit);


/* 
 * Bit2_map_col_major
 * Input: a Bit2 matrix, a function to apply onto the matrix, and a void 
 *        pointer to use as a closure
 * Output: none
 * Description: applies a function f to every element in the matrix Bit2 in
 *              column-major fashion, starting from (col, row) = (0,0) and
 *              applying f to each element in the column before applying to
 *              the next column
 * Logical Expectation: Bit2 is not null, function f has the given 5 params
 * 
*/
extern void Bit2_map_col_major(T Bit2, void f(int, int, T, int, void*),
                                                                    void*);


/* 
 * Bit2_map_row_major
 * Input: a Bit2 matrix, a function to apply onto the matrix, and a void 
 *        pointer to use as a closure
 * Output: none
 * Description: applies a function f to every element in the matrix Bit2 in
 *              row-major fashion, starting from (col, row) = (0,0) and
 *              applying f to each element in a row before applying to the
 *              next row
 * Logical Expectation: Bit2 is not null, function f has the given 5 params
*/
extern void Bit2_map_row_major(T Bit2, void f(int, int, T, int, void*),
                                                                    void*);


/*
 * Bit2_free
 * Input: a pointer to a Bit2 matrix
 * Output: none
 * Description: deallocates memory associated with Bit2 vector
 * Logical Expectation: Bit2 is not null
 * 
*/
extern void Bit2_free(T *Bit2);

#undef T
# endif